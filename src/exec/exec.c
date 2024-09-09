/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/09 17:08:54 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(int input_test, t_execom *execom, t_data *data)
{
	if (input_test)
	{
		execom->fdstdin = dup(STDIN_FILENO);
		execom->fdstdout = dup(STDOUT_FILENO);
	}
	else
	{
		if (dup2(execom->fdstdin, STDIN_FILENO) == -1)
		{
			close(execom->fdstdin);
			perror("error close fdstdin");
			exit_clean(data, NOTHING, N_EXIT);

		}
		if (dup2(execom->fdstdout, STDOUT_FILENO) == -1)
		{
			close(execom->fdstdout);
			perror("error close fdstdout");
			exit_clean(data, NOTHING, N_EXIT);
		}
		close(execom->fdstdin);
		close(execom->fdstdout);
	}
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

void	wait_children(int id, int status)
{
	if (!WIFEXITED(status))
		perror("Erreur pendant l'attente d'un processus enfant");
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

void	dup_stdin(int prev_fd, t_data *data)
{
	if (dup2(prev_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin failed");
    	exit_clean(data, NOTHING, N_EXIT);
	}
	close(prev_fd);
}

void	dup_stdout(int pipe_fd[2], t_data *data)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout failed");
    	exit_clean(data, NOTHING, N_EXIT);
	}
	close(pipe_fd[1]);
}

void	exec_line(t_exec *exec, t_data *data)
{
	char	*args;

	if (access(exec->cmd, F_OK | X_OK) == 0)
		args = exec->cmd;
	else
		args = my_get_path(exec->cmd, data);
	if (execve(args, exec->args, my_env_to_tab(data->my_env) == -1))
	{
		free(args);
		free(exec->args);
		exit_clean(data, NOTHING, Y_EXIT);
	}
}


void	output_redir(t_exec *exec, t_data *data)
{
	int	fdoutput;
	int	flags;
	int success;
	int	failure;

	success = 0;
	failure = 0;
	while (exec->redir && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
	{
		if (exec->redir->filename[0] == '$')
		{
			fprintf(stderr, "%s: ambiguous redirect\n", exec->redir->filename);
			failure = 1;
			break ;
		}
		else
		{
			success = 1;
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
			exec->redir->type == APPEND_TK) && exec->redir->next->filename[0] != '$')
				close(fdoutput);
			exec->redir = exec->redir->next;
		}
	}
	if (success)
	{
		if (dup2(fdoutput, STDOUT_FILENO) == -1)
		{
			perror("dup2 output redirection failed");
			exit_clean(data, NOTHING, N_EXIT);
		}
		close(fdoutput);
	}
}
/*
void	output_redir(t_exec *exec)
{
	int	fdoutput;
	int	flags;

	while (exec->redir && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
	{
		if (exec->redir->type == APPEND_TK)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fdoutput = open(exec->redir->filename, flags, 0644);
		if (fdoutput == -1) 
		{
			perror(exec->redir->filename);
			exit(EXIT_FAILURE);
		}
		if (exec->redir->next && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
			close(fdoutput);
		exec->redir = exec->redir->next;
	}
	if (dup2(fdoutput, STDOUT_FILENO) == -1)
	{
		perror("dup2 output redirection failed");
		exit(EXIT_FAILURE);
	}
	close(fdoutput);
}
*/

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
	if (dup2(fdinput, STDIN_FILENO) == -1)
	{
		perror("dup2 input redirection failed");
		exit_clean(data, NOTHING, N_EXIT);
	}
	close(fdinput);
}

void	child_process(t_exec *exec, int pipe_fd[2], int prev_fd, t_data *data, t_execom execom)
{
	close(execom.fdstdin);
	close(execom.fdstdout);
	if (exec->redir && exec->redir->type == INPUT_TK)
		input_redir(exec, data);
	else if (prev_fd != -1)
		dup_stdin(prev_fd, data);
	if (exec->redir && (exec->redir->type == OUTPUT_TK || \
		exec->redir->type == APPEND_TK))
		output_redir(exec, data);
	if (exec->next)
		dup_stdout(pipe_fd, data);
	exec_line(exec, data);
}

int	exec_cmd(t_data *data, char **envp)
{
	t_exec		*exec;
	t_exec		*exec_temp;
	t_execom	execom;
	int			id;
	int			pipe_fd[2];
	int			prev_fd;
	int			status;

	exec = data->head;
	exec_temp = exec;
	prev_fd = -1;
	init_fd(1, &execom, data);
	while (exec_temp)
	{
		if (exec_temp->next)
			pipe(pipe_fd);
		if (verif_builtin(data, exec_temp) == 0)
		{
			id = create_child_process(data);
			if (id == 0)
				child_process(exec_temp, pipe_fd, prev_fd, data, execom);
			close_fds(exec_temp, pipe_fd, &prev_fd);
			exec_temp = exec_temp->next;
		}
		else
			exec_temp = exec_temp->next;
	}
	while ((id = waitpid(-1, &status, 0)) > 0)
		wait_children(id, status);
	init_fd(0, &execom, data);
	return (0);
}
