/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:41 by apernot           #+#    #+#             */
/*   Updated: 2024/09/26 17:08:19 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (temp->type == INPUT_TK)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	output_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (temp->type == OUTPUT_TK || temp->type == APPEND_TK)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	error_exec(char *path, int error_nb)
{
	struct stat	file_stat;

	if ((error_nb == 13 && stat(path, &file_stat) != -1)
		|| is_absolute_path(path))
	{
		if (S_ISDIR(file_stat.st_mode))
			ft_fprintf("minishell: %s: Is a directory\n", path);
		else
		{
			ft_fprintf("minishell: %s: ", path);
			ft_fprintf(strerror(error_nb));
			ft_fprintf("\n");
		}
	}
	else
		ft_fprintf("minishell: %s: command not found\n", path);
}

void	total_unlink(t_data *data)
{
	t_exec	*exec;
	t_redir	*temp;

	exec = data->head;
	while (exec)
	{
		temp = exec->redir;
		while (temp)
		{
			if (temp->type == HEREDOC_TK)
				unlink(temp->filename);
			temp = temp->next;
		}
		exec = exec->next;
	}
}
