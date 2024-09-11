/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:30:29 by apernot           #+#    #+#             */
/*   Updated: 2024/09/11 17:09:59 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exec(char *path, int error_nb)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2_clean(STDERR_FILENO, STDOUT_FILENO);
	if (error_nb == 2)
		printf("%s: command not found\n", path);	
	else if (error_nb == -2)
		printf("%s: Is a directory\n", path);
	else if (error_nb == 13)
		printf("%s: Permission denied\n", path);
	dup2_clean(fd_tmp, STDOUT_FILENO);
}

