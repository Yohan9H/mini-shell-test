/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/02 16:32:18 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_child_process(void)
{
	int	id;

	id = fork();
	if (id < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (id);
}

int	exec_cmd(t_data *data, char **envp)
{
	t_exec *exec;
	int id;
	int pipe_fd[2];
	int	prev_fd;
	int fdinput;
	int	fdoutput;
	int flags;
	char	*args;

	exec = data->head;
	prev_fd = -1;
	while (exec)
	{
		pipe(pipe_fd);
		id = create_child_process();
		if (id == 0)
		{
			if (exec->redir && exec->redir->type == INPUT_TK)
			{
				fdinput = open(exec->redir->filename, O_RDONLY);
				if (dup2(fdinput, STDIN_FILENO) == -1)
				{
					perror("open");
					return (-1);
				}
				close(fdinput);
			}
			else if (prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					return (-1);
			}
			if (exec->redir && exec->redir->type == OUTPUT_TK)
			{
				flags = O_WRONLY | O_CREAT | O_TRUNC;
				fdoutput = open(exec->redir->filename, flags);
				if (dup2(fdoutput, STDOUT_FILENO) == -1)
					return (-1);
			}
			if (exec->next)
			{
				close(pipe_fd[0]);
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
					return (-1);
			}
			
			if (access(exec->cmd, F_OK | X_OK) == 0)
				args = exec->cmd;
			else
				args = my_get_path(exec->cmd, envp);
			if (execve(args, exec->args, envp) == -1)
			{
				exit(EXIT_FAILURE);
			}
		}
		prev_fd = pipe_fd[0];
	}
	return (0);
}
