/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:30:29 by apernot           #+#    #+#             */
/*   Updated: 2024/09/23 11:25:45 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exec(t_data *data, char *path, int error_nb)
{
	struct stat	file_stat;

	if (error_nb == 2)
	{
		data->exit_code = 127;
		ft_fprintf("minishell: %s: command not found\n", path);
	}	
	else if (error_nb == -2)
	{
		data->exit_code = 126;
		ft_fprintf("minishell: %s: Is a directory\n", path);
	}
	else if (error_nb == 13 && stat(path, &file_stat) != -1)
	{
		data->exit_code = 1;
		if (S_ISDIR(file_stat.st_mode))
			ft_fprintf("minishell: %s: Is a directory\n", path);
		else
			ft_fprintf("minishell: %s: Permission denied\n", path);
	}
	else if (error_nb == 0)
	{
		data->exit_code = 127;
		ft_fprintf("minishell: %s: No such file or directory\n", path);
	}
}
