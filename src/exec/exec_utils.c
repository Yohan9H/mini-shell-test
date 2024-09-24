/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:48:13 by apernot           #+#    #+#             */
/*   Updated: 2024/09/24 22:43:17 by arthur           ###   ########.fr       */
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

void	wait_children(int id, t_data *data)
{
	int	status;

	id = waitpid(-1, &status, 0);
	while (id > 0)
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
	}
	return (0);
}

void	close_fds(t_exec *exec, t_execom *execom)
{
	if (execom->prev_fd != -1)
		close(execom->prev_fd);
	if (exec->next && execom->pipe_fd[0] != -1)
		dup2(execom->pipe_fd[0], execom->prev_fd);
	close(execom->pipe_fd[0]);
	close(execom->pipe_fd[1]);
}
