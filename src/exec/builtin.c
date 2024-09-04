/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:24:21 by apernot           #+#    #+#             */
/*   Updated: 2024/09/04 16:41:02 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cd(char *path)
{
	if (chdir(path) == -1)
		perror("chdir()");
}

void	built_in_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		if (getcwd(buf, sizeof(buf)) != NULL)
			printf("%s\n", buf);
		else
			perror("getcwd()");
	}
}

void	built_in_exit(void)
{
}
