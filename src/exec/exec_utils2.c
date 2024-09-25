/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:41 by apernot           #+#    #+#             */
/*   Updated: 2024/09/25 17:17:54 by apernot          ###   ########.fr       */
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

void	error_exec(t_data *data, char *path, int error_nb)
{
	struct stat	file_stat;

	if (error_nb == 2)
		ft_fprintf("minishell: %s: command not found\n", path);
	else if (error_nb == -2)
		ft_fprintf("minishell: %s: Is a directory\n", path);
	else if (error_nb == 13 && stat(path, &file_stat) != -1)
	{
		if (S_ISDIR(file_stat.st_mode))
			ft_fprintf("minishell: %s: Is a directory\n", path);
		else
			ft_fprintf("minishell: %s: Permission denied\n", path);
	}
	else if (error_nb == 0)
		ft_fprintf("minishell: %s: No such file or directory\n", path);
}
