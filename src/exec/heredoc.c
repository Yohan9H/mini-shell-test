/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:54:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/06 14:43:39 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc (t_exec *exec, int fd_out)
{
	char 	*line;
	char	*tmp;

	while(1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strncmp(line, exec->redir->filename, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		ft_putstr_fd(tmp, fd_out);
		free(line);
		free(tmp);
	}
}
