/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:30:29 by apernot           #+#    #+#             */
/*   Updated: 2024/09/19 13:35:53 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exec(t_data *data, char *path, int error_nb)
{
	if (error_nb == 2)
	{
		data->exit_code = 127;
		ft_fprintf("minishell %s: command not found\n", path);
	}	
	else if (error_nb == -2)
	{
		data->exit_code = 126;
		ft_fprintf("minishell %s: Is a directory\n", path);
	}
	else if (error_nb == 13)
	{
		data->exit_code = 1;
		ft_fprintf("minishell %s: Permission denied\n", path);
	}
}

