/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/12 15:01:04 by aper9not          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_clean(int in, int out)
{
	if (dup2(in, out) == -1)
		perror("dup2 error");
	close(in);
}

void	init_fd(int input_test, t_execom *execom)
{
	if (input_test)
	{
		execom->fdstdin = dup(STDIN_FILENO);
		execom->fdstdout = dup(STDOUT_FILENO);
	}
	else
	{
		dup2_clean(execom->fdstdin, STDIN_FILENO);
		dup2_clean(execom->fdstdout, STDOUT_FILENO);
	}
}


void wait_children(int id, t_data *data)
{
	int	status;

	id = waitpid(-1, &status, 0);
	while (id  > 0)
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			 if (WTERMSIG(status) == SIGQUIT)
			 	ft_fprintf("Quit (core dumped)\n");
			 g_var_global = 128 + WTERMSIG(status);
			 data->exit_code = g_var_global;
		}
		id = waitpid(-1, &status, 0);
	}
}

int	exec_line(t_exec *exec, t_data *data)
{
	char	*path;
	char	**env;

	if (!exec->cmd)
		return (0);
	if (exec->cmd[0] == '\0')
		error_exec(data, exec->cmd, 2);
	path = my_get_path(exec->cmd, data);
	if (!path)
		return (error_exec(data, exec->cmd, errno), -1);
	env = my_env_to_tab(data->my_env);
	if (!env)
		return (free(path), -1);
	if (!exec->args)
		return (free(path), freetab(env), -1);
	if (execve(path, exec->args, env) == -1)
	{
		error_exec(data, exec->cmd, errno);
		free(path);
		freetab(env);
		return (-2);
	}
	return (0);
}


int	open_clean(t_exec *exec, t_data *data)
{
	int	fd;
	int flags;

	if (exec->redir->type == APPEND_TK)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (exec->redir->type == OUTPUT_TK)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (exec->redir->type == INPUT_TK)
		fd = open(exec->redir->filename, O_RDONLY);
	else
		fd = open(exec->redir->filename, flags, 0644);
	if (fd == -1) 
	{
		perror(exec->redir->filename);
		exit_clean(data, NOTHING, C_EXIT);
		exit (1);
	}
	return (fd);
}

void	redir(t_redir *redir, t_exec *exec, t_data *data)
{
	int fdinput;
	int fdoutput;
	t_redir *temp;
	
	temp = redir;
	while (temp)
	{
		if (temp->type == INPUT_TK)
		{
			fdinput = open_clean(exec, data);
			dup2_clean(fdinput, STDIN_FILENO);
		}
		else if ((temp->type == OUTPUT_TK || temp->type == APPEND_TK))
		{
			fdoutput = open_clean(exec, data);
			dup2_clean(fdoutput, STDOUT_FILENO);
		}
		temp = temp->next;
	}
}

void	init_pipes(int pipe_fd[2], t_data *data)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit_clean(data, NOTHING, N_EXIT);
	}
}
void	close_fds(t_exec *exec, int pipe_fd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (exec->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else if (*prev_fd != -1)
		close(pipe_fd[0]);
}

void	child_process(t_exec *exec, int pipe_fd[2], int prev_fd, t_data *data, t_execom execom)
{
	int exit_code;

	exit_code = 0;

	signal(SIGQUIT, SIG_DFL);
	close(execom.fdstdin);
	close(execom.fdstdout);
	redir(exec->redir, exec, data);
	if (prev_fd != -1)
		dup2_clean(prev_fd, STDIN_FILENO);
	if (exec->next)
	{
		close(pipe_fd[0]);
		dup2_clean(pipe_fd[1], STDOUT_FILENO);
	}
	if (verif_builtin(data, exec, &execom) == 0)
		exit_code = exec_line(exec, data);
	exit_clean(data, NOTHING, C_EXIT);
	if (exit_code == -2)
		exit (IS_A_DIRECTORY);
	exit (COMMAND_NOT_FOUND);
}

int	create_child_process(t_data *data)
{
	int	id;

	id = fork();
	if (id < 0)
	{
		perror("fork");
		exit_clean(data, NOTHING, N_EXIT);
	}
	return (id);
}

int	builtin_redir(t_exec *exec, t_data *data, t_execom *execom)
{
	if (exec->next == NULL && is_builtin(data, exec) == 1)
	{
		redir(exec->redir, exec, data);
		if (exec->cmd)
			verif_builtin(data, exec, execom);
		return (1);
	}
	return (0);
}
int	is_cmd(t_exec *exec, t_data *data)
{
	while (exec)
	{
		if (exec->cmd)
			return (1);
		exec = exec->next;
	}
	data->exit_code = 0;
	return (0);
}

int	exec_cmd2(t_data *data, t_execom *execom)
{
	t_exec		*exec;
	t_exec		*exec_temp;
	int			id;
	int			pipe_fd[2];
	int			prev_fd;

	exec = data->head;
	exec_temp = exec;
	prev_fd = -1;
	if (builtin_redir(exec_temp, data, execom) == 1)
		return (0);
	while (exec_temp)
	{
		if (!is_cmd(exec_temp, data))
			return (0);
		if (exec_temp->next)
			init_pipes(pipe_fd, data);
		id = create_child_process(data);
		if (id == 0)
			child_process(exec_temp, pipe_fd, prev_fd, data, *execom);
		close_fds(exec_temp, pipe_fd, &prev_fd);
		exec_temp = exec_temp->next;
	}
	wait_children(id, data);
	return (0);
}

int exec_cmd(t_data *data)
{
	t_execom	execom;

	init_fd(1, &execom);
	exec_cmd2(data, &execom);
	init_fd(0, &execom);
	return (0);
}
