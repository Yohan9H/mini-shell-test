/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:24:21 by apernot           #+#    #+#             */
/*   Updated: 2024/09/06 13:26:47 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_data *data, char *path)
{
	if (path == NULL || path[0] == '\0')
	{
		path = give_value_env("HOME", data, 4);
		if (path == NULL)
		{
			fprintf(stderr, "cd : HOME not set\n");
			return (1);
		}
	}
	if (chdir(path) == -1)
		perror("chdir()");
	return (1);
}

int	builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		perror("getcwd() error");
	return (1);
}

int	builtin_exit(t_data *data)
{
	printf("exit\n");
	exit_clean(data, NOTHING, Y_EXIT);
	return (1);
}

int	builtin_env(t_data *data)
{
	t_env *lst;

	lst = data->my_env;
	while (lst != NULL)
	{
		printf("%s\n", lst->line);
		lst = lst->next;
	}
	return (1);
}
