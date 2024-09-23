/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:32:47 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/23 13:02:01 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_tokentype type)
{
	if (type == INPUT_TK || type == OUTPUT_TK || type == APPEND_TK
		|| type == HEREDOC_TK)
		return (1);
	else
		return (0);
}

int	check_if_break(t_data *data, char *line, char *eof, int fd)
{
	if (g_var_global == 1)
	{
		if (line)
			free(line);
		data->code_reset = 1;
		data->exit_code = 130;
		g_var_global = 0;
		return (1);
	}
	if (line == NULL)
	{
		ft_putstr_fd("\n", fd);
		return (1);
	}
	if (strncmp(line, eof, ft_strlen(eof)) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}
