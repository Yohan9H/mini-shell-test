/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:48:13 by apernot           #+#    #+#             */
/*   Updated: 2024/09/26 14:13:07 by yohurteb         ###   ########.fr       */
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
				g_var_global = 0;
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

void	close_fds(t_execom *execom)
{
	close(execom->pipe_fd[0]);
	close(execom->pipe_fd[1]);
}
