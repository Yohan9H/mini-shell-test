/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/04 13:53:35 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(int input_test)
{
	int fdstdin;
	int	fdstdout;

	if (input_test)
	{
		fdstdin = dup(STDIN_FILENO);
		fdstdout = dup(STDOUT_FILENO);
	}
	else
	{
		if (dup2(fdstdin, STDIN_FILENO) == -1)
			return (-1);
		if (dup2(fdstdout, STDOUT_FILENO) == -1)
			return (-1);
	}
}


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

void	wait_children(int id)
{
	int status;
	
	while ((id = waitpid(-1, &status, 0)) > 0)
    {
        if (!WIFEXITED(status)) {
            printf("Processus enfant %d terminé avec le code de sortie %d.\n", id, WEXITSTATUS(status));
        } else {
            perror("Erreur pendant l'attente d'un processus enfant");
        }
    }
}

void	close_fds(t_exec **exec, int pipe_fd[2], int prev_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if ((*exec)->next)
	{
		close(pipe_fd[1]);
		prev_fd = pipe_fd[0];
	}
	else
		close(pipe_fd[0]);
	(*exec) = (*exec)->next;
}

void	exec_line(t_exec *exec, char **envp)
{
	char	*args;

	if (access(exec->cmd, F_OK | X_OK) == 0)
		args = exec->cmd;
	else
		args = my_get_path(exec->cmd, envp);
	if (execve(args, exec->args, envp) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

void	output_redir(t_exec *exec)
{
	int fdoutput;
	int	flags;
	
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

void	input_redir(t_exec *exec)
{
	int	fdinput;

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

int	exec_cmd(t_data *data, char **envp)
{
	t_exec *exec;
	int id;
	int childpid;
	int pipe_fd[2];
	int	prev_fd;

	exec = data->head;
	prev_fd = -1;

	init_fd(1);
	while (exec)
	{
		if (exec->next)
			pipe(pipe_fd);
		id = create_child_process();
		if (id == 0)
		{
			if (exec->redir && exec->redir->type == INPUT_TK) //redirection input
				input_redir(exec);
			else if (prev_fd != -1) //commande suivante sans redirection
			{
				printf("process enfant avant 3eme check");
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					return (-1);
				close(prev_fd);
			}
			if (exec->redir && exec->redir->type == OUTPUT_TK) //redirection output
				output_redir(exec);
			if (exec->next) // ecriture dans le pipe pour la commande suivante
			{
				printf("process enfant avant 5eme check");
				close(pipe_fd[0]);
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
					return (-1);
				close(pipe_fd[1]);
			}
			exec_line(exec, envp);
		}
		close_fds(&exec, pipe_fd, prev_fd);
	}
	wait_children(id);
	init_fd(0);
	return (0);
}
