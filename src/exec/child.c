/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:40:47 by apernot           #+#    #+#             */
/*   Updated: 2024/09/23 11:55:00 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_line(t_exec *exec, t_data *data)
{
	char	*path;
	char	**env;

	if (!exec->cmd)
		return (0);
	if (exec->cmd[0] == '\0')
		error_exec(data, exec->cmd, 2);
	path = my_get_path(exec->cmd, data);
	if (!path)
		return (error_exec(data, exec->cmd, errno), -1);
	env = my_env_to_tab(data->my_env);
	if (!env)
		return (free(path), -1);
	if (!exec->args)
		return (free(path), freetab(env), -1);
	if (execve(path, exec->args, env) == -1)
	{
		error_exec(data, exec->cmd, errno);
		free(path);
		freetab(env);
		return (-2);
	}
	return (0);
}

int	open_clean(t_exec *exec, t_data *data)
{
	int	fd;
	int	flags;

	if (exec->redir->type == APPEND_TK)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (exec->redir->type == OUTPUT_TK)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (exec->redir->type == INPUT_TK)
		fd = open(exec->redir->filename, O_RDONLY);
	else
		fd = open(exec->redir->filename, flags, 0644);
	if (fd == -1)
	{
		perror(exec->redir->filename);
		exit_clean(data, NOTHING, C_EXIT);
		exit (1);
	}
	return (fd);
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

void	child_process(t_exec *exec,	t_data *data, t_execom *execom)
{
	int	exit_code;

	exit_code = 0;
	signal(SIGQUIT, SIG_DFL);
	close(execom->fdstdin);
	close(execom->fdstdout);
	redir(exec->redir, exec, data);
	if (execom->prev_fd != -1)
		dup2_clean(execom->prev_fd, STDIN_FILENO);
	if (exec->next)
	{
		close(execom->pipe_fd[0]);
		dup2_clean(execom->pipe_fd[1], STDOUT_FILENO);
	}
	if (verif_builtin(data, exec, execom) == 0)
		exit_code = exec_line(exec, data);
	exit_clean(data, NOTHING, C_EXIT);
	if (exit_code == -2)
		exit (IS_A_DIRECTORY);
	exit (COMMAND_NOT_FOUND);
}
