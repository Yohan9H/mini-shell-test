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
			data->exit_code = WTERMSIG(status);
		id = waitpid(-1, &status, 0);
	}
}

int	exec_line(t_exec *exec, t_data *data)
{
	char	*path;
	char	**env;

	if (!exec->cmd)
		return (0);
	path = my_get_path(exec->cmd, data);
	if (!path)
		return (error_exec(exec->cmd, errno), -1);
	env = my_env_to_tab(data->my_env);
	if (!env)
		return (free(path), -1);
	if (!exec->args)
		return (free(path), freetab(env), -1);
	if (execve(path, exec->args, env) == -1)
	{
		error_exec(exec->cmd, errno);
		free(path);
		freetab(env);
		return (-2);
	}
	return (0);
}

int	output_redir_success(t_exec *exec, t_data *data)
{
	int	fdoutput;
	int	flags;
	
	if (exec->redir->type == APPEND_TK)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fdoutput = open(exec->redir->filename, flags, 0644);
	if (fdoutput == -1) 
	{
		perror(exec->redir->filename);
		return (-1);
	}
	if (exec->redir->next && (exec->redir->type == OUTPUT_TK || \
	exec->redir->type == APPEND_TK))
		close(fdoutput);
	return (fdoutput);
}

void	output_redir(t_exec *exec, t_data *data)
{
	int	fdoutput;

	while (exec->redir && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
	{
		fdoutput = output_redir_success(exec, data);
		if (fdoutput == -1)
			return ;
		exec->redir = exec->redir->next;
	}
	dup2_clean(fdoutput, STDOUT_FILENO);
}

void	input_redir(t_exec *exec, t_data *data)
{
	int	fdinput;

	while (exec->redir && exec->redir->type == INPUT_TK)
	{
		fdinput = open(exec->redir->filename, O_RDONLY);
		if (fdinput == -1) 
		{
			perror(exec->redir->filename);
			exit_clean(data, NOTHING, Y_EXIT);
		}
		if (exec->redir->next && exec->redir->next->type == INPUT_TK)
			close(fdinput);
		exec->redir = exec->redir->next;
	}
	dup2_clean(fdinput, STDIN_FILENO);
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
	int	exit_code;
	
	exit_code = -1;
	close(execom.fdstdin);
	close(execom.fdstdout);
	if (exec->redir && exec->redir->type == INPUT_TK)
		input_redir(exec, data);
	else if (prev_fd != -1)
		dup2_clean(prev_fd, STDIN_FILENO);
	if (exec->redir && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
		output_redir(exec, data);
	if (exec->next)
	{
		close(pipe_fd[0]);
		dup2_clean(pipe_fd[1], STDOUT_FILENO);
	}
	if (verif_builtin(data, exec, &execom) == 0)
		data->exit_code = exec_line(exec, data);
	if (data->exit_code == -2)
	{
		exit_clean(data, NOTHING, Y_EXIT);
		// add exit number to exit clean
	}
		exit_clean(data, NOTHING, Y_EXIT);
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
		if (exec->redir && exec->redir->type == INPUT_TK)
			input_redir(exec, data);
		if (exec->redir && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
			output_redir(exec, data);
		if (exec->cmd)
			verif_builtin(data, exec, execom);
		return (0);
	}
}

int	exec_cmd2(t_data *data, t_execom *execom)
{
	t_exec		*exec;
	t_exec		*exec_temp;
	int			id;
	int			pipe_fd[2];
	int			prev_fd;
	int			status;

	exec = data->head;
	exec_temp = exec;
	prev_fd = -1;
	if (builtin_redir(exec_temp, data, execom) == 0)
		return (0); // faire une verif avant du nombre de commande ?
	while (exec_temp)
	{
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
