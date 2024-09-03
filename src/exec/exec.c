/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/03 15:33:57 by apernot          ###   ########.fr       */
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
	int childpid;
	int pipe_fd[2];
	int	prev_fd;
	int fdinput;
	int	fdoutput;
	int flags;
	int status;
	char	*args;
	int fdstdin;
	int	fdstdout;

	exec = data->head;
	prev_fd = -1;

 	fdstdin = dup(STDIN_FILENO);
	fdstdout = dup(STDOUT_FILENO);
	
	while (exec)
	{
		if (exec->next)
			pipe(pipe_fd);
		id = create_child_process();
		if (id == 0)
		{
			printf("process enfant avant 1er check");
			if (exec->redir && exec->redir->type == INPUT_TK)
			{
				printf("process enfant avant 2eme check");
				while (exec->redir && exec->redir->type == INPUT_TK)
				{
					fdinput = open(exec->redir->filename, O_RDONLY);
					if (exec->redir->next && exec->redir->next->type == INPUT_TK)
						close(fdinput);
					exec->redir = exec->redir->next;
				}
				if (dup2(fdinput, STDIN_FILENO) == -1)
				{
					perror("open");
					return (-1);
				}
				close(fdinput);
			}
			else if (prev_fd != -1)
			{
				printf("process enfant avant 3eme check");
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					return (-1);
				close(prev_fd);
			}
			if (exec->redir && exec->redir->type == OUTPUT_TK)
			{
				printf("process enfant avant 4eme check");
				while (exec->redir && exec->redir->type == OUTPUT_TK)
				{
					
					flags = O_WRONLY | O_CREAT | O_TRUNC;
					fdoutput = open(exec->redir->filename, flags, 0644);
					if (exec->redir->next && exec->redir->type == OUTPUT_TK)
						close(fdoutput);
					exec->redir = exec->redir->next;
				}
				if (dup2(fdoutput, STDOUT_FILENO) == -1)
					return (-1);
				close(fdoutput);
			}
			if (exec->next)
			{
				printf("process enfant avant 5eme check");
				close(pipe_fd[0]);
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
					return (-1);
				close(pipe_fd[1]);
			}
			
			if (access(exec->cmd, F_OK | X_OK) == 0)
				args = exec->cmd;
			else
				args = my_get_path(exec->cmd, envp);
			printf("process enfant avant 6eme check");
			if (execve(args, exec->args, envp) == -1)
			{
				exit(EXIT_FAILURE);
			}
		}
		if (prev_fd != -1)
		{
			close(prev_fd);
		}
		if (exec->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			close(pipe_fd[0]);
		exec = exec->next;
	}
	while ((id = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status)) {
            printf("Processus enfant %d terminé avec le code de sortie %d.\n", id, WEXITSTATUS(status));
        } else {
            perror("Erreur pendant l'attente d'un processus enfant");
        }
    }
	if (dup2(fdstdin, STDIN_FILENO) == -1)
					return (-1);
	if (dup2(fdstdout, STDOUT_FILENO) == -1)
					return (-1);
	return (0);
}
