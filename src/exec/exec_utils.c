/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:48:13 by apernot           #+#    #+#             */
/*   Updated: 2024/09/25 13:42:32 by apernot          ###   ########.fr       */
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

void	wait_children(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->pid_count)
	{
		if (waitpid(data->pids[i], &status, 0))
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
		}
		i++;
	}
}

void	init_pipes(t_execom *execom, t_data *data)
{
	if (pipe(execom->pipe_fd) == -1)
	{
		perror("pipe");
		exit_clean(data, NOTHING, N_EXIT);
	}
}

int	input_redir(t_redir *redir)
{
	t_redir *temp;

	temp = redir;
	while (temp)
	{
		if (temp->type == INPUT_TK)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int output_redir(t_redir *redir)
{
	t_redir *temp;

	temp = redir;
	while (temp)
	{
		if (temp->type == OUTPUT_TK || temp->type == APPEND_TK)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	close_fds(t_exec *exec, t_execom *execom)
{
	close(execom->pipe_fd[0]);
	close(execom->pipe_fd[1]);
}
