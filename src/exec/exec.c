/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/30 11:14:59 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_redir *redir, t_data *data, t_execom *execom)
{
	int		fdinput;
	int		fdoutput;
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (temp->type == OUTPUT_TK || temp->type == APPEND_TK)
		{
			fdoutput = open_clean(temp, data, execom);
			dup2_clean(fdoutput, STDOUT_FILENO);
		}
		if (temp->type == INPUT_TK || temp->type == HEREDOC_TK)
		{
			fdinput = open_clean(temp, data, execom);
			dup2_clean(fdinput, STDIN_FILENO);
		}
		temp = temp->next;
	}
}

int	builtin_redir(t_exec *exec, t_data *data, t_execom *execom)
{
	if (exec->next == NULL && is_builtin(data, exec) == 1)
	{
		redir(exec->redir, data, execom);
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

	exec = data->head;
	if (builtin_redir(exec, data, execom) == 1)
		return (0);
	while (exec)
	{
		execom->pipe_fd[0] = -1;
		execom->pipe_fd[1] = -1;
		if (!is_cmd(exec, data))
			return (0) ; // a cause de lui on unlink pas les alone heredocs il faut faire un break
		init_pipes(execom, data);
		signal(SIGINT, handle_sigint_cat);
		data->pids[data->pid_count] = create_child_process(data);
		if (data->pids[data->pid_count] == 0)
			child_process(exec, data, execom);
		dup2(execom->pipe_fd[0], STDIN_FILENO);
		close_fds(execom);
		data->pid_count = data->pid_count + 1;
		exec = exec->next;
	}
	wait_children(data);
	total_unlink(data);
	data->pid_count = 0;
	return (0);
}

int	exec_cmd(t_data *data)
{
	t_execom	execom;

	g_var_global = 0;
	execom.pipe_fd[0] = -1;
	execom.pipe_fd[1] = -1;
	data->pids = (pid_t *)malloc(sizeof(pid_t) \
		* (ft_lstsize_exec(data->head) + 1));
	if (!data->pids)
		exit_clean(data, MALLOC, Y_EXIT);
	init_fd(1, &execom);
	exec_cmd2(data, &execom);
	init_fd(0, &execom);
	return (0);
}
