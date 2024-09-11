/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/11 14:13:28 by apernot          ###   ########.fr       */
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

void	wait_children(int id, int status)
{
	if (!WIFEXITED(status))
		perror("Erreur pendant l'attente d'un processus enfant");
}



// void	dup_stdin(int prev_fd)
// {
// 	dup2_clean(prev_fd, STDIN_FILENO);
// }

// void	dup_stdout(int pipe_fd[2], t_data *data)
// {
// 	close(pipe_fd[0]);
// 	dup2_clean(pipe_fd[1], STDOUT_FILENO);
// }



// int	exec_line(t_exec *exec, t_data *data)
// {
// 	char	*path;

// 	if (access(exec->cmd, F_OK | X_OK) == 0)
// 		path = exec->cmd;
// 	else
// 		path = my_get_path(exec->cmd, data);
// 	if (execve(path, exec->args, my_env_to_tab(data->my_env) == -1))
// 	{
// 		free(path);
// 		free(exec->args);
// 		return (-2);
// 	}
// 	return (0);
// }

int	exec_line(t_exec *exec, t_data *data)
{
	char	*path;
	char	**env;

	if (!exec->cmd)
		return (0);
	path = my_get_path(exec->cmd, data);
	if (!path)
		return (-1);
	if (access(exec->cmd, F_OK | X_OK) == 0)
		path = exec->cmd;
	else
		path = my_get_path(exec->cmd, data);
	env = my_env_to_tab(data->my_env);
	if (!env)
		return (free(path), -1);
	if (!exec->args)
		return (free(path), -1);
	if (execve(path, exec->args, my_env_to_tab(data->my_env) == -1))
	{
		free(path);
		free(exec->args);
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
		exit_clean(data, NOTHING, N_EXIT);
	}
	if (exec->redir->next && (exec->redir->type == OUTPUT_TK || \
	exec->redir->type == APPEND_TK))
		close(fdoutput);
	return (fdoutput);
}

void	output_redir(t_exec *exec, t_data *data)
{
	int	fdoutput;
	int	flags;

	while (exec->redir && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
	{
		fdoutput = output_redir_success(exec, data);
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
			exit_clean(data, NOTHING, N_EXIT);
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
	exit_code = exec_line(exec, data);
	if (exit_code == -2)
		exit (IS_A_DIRECTORY);
	exit (COMMAND_NOT_FOUND);
}
// int	create_child_process(t_data *data, t_exec *exec, int pipe_fd[2], int prev_fd, t_execom execom)
// {
// 	int	id;

// 	id = fork();
// 	if (id < 0)
// 	{
// 		perror("fork");
// 		exit_clean(data, NOTHING, N_EXIT);
// 	}
// 	if (id == 0)
// 		child_process(exec, pipe_fd, prev_fd, data, execom);
// 	close_fds(exec, pipe_fd, &prev_fd);
// 	return (id);
// }

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


// int	exec_cmd2(t_data *data, char **envp)
// {
// 	t_exec		*exec;
// 	t_exec		*exec_temp;
// 	t_execom	execom;
// 	int			id;
// 	int			pipe_fd[2];
// 	int			prev_fd;
// 	int			status;

// 	exec = data->head;
// 	exec_temp = exec;
// 	prev_fd = -1;
// 	init_fd(1, &execom, data);
// 	while (exec_temp)
// 	{
// 		if (exec_temp->next)
// 			init_pipes(pipe_fd, data);
// 		if (verif_builtin(data, exec_temp) == 0)
// 			id = create_child_process(data, exec_temp, pipe_fd, prev_fd, execom);
// 		exec_temp = exec_temp->next;
// 	}
// 	while ((id = waitpid(-1, &status, 0)) > 0)
// 		wait_children(id, status);
// 	init_fd(0, &execom, data);
// 	return (0);
// }



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
	while (exec_temp)
	{
		if (exec_temp->next)
			init_pipes(pipe_fd, data);
		if (verif_builtin(data, exec_temp) == 0)
		{
			id = create_child_process(data);
			if (id == 0)
				child_process(exec_temp, pipe_fd, prev_fd, data, *execom);
			close_fds(exec_temp, pipe_fd, &prev_fd);
		}
		exec_temp = exec_temp->next;
	}
	while ((id = waitpid(-1, &status, 0)) > 0)
		wait_children(id, status);
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