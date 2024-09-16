/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:24:21 by apernot           #+#    #+#             */
/*   Updated: 2024/09/16 13:49:45 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_nb_parameter(char **args)
{
	int		j;
	int		nb;

	nb = 0;
	j = 1;
	while (args[j])
	{
		j++;
		nb++;
	}
	if (nb > 1)
		return (1);
	return (0);
}

int	builtin_cd(t_data *data, char **args)
{
	char	*home;

	if (verif_nb_parameter(args) == 1)
	{
		fprintf(stderr, "cd : too many arguments\n");
		return (1);
	}
	home = ft_strdup(args[1]);
	if (args[1] == NULL || args[1][0] == '\0')
	{
		free(home);
		home = give_value_env("HOME", data, 4);
		if (home == NULL)
		{
			fprintf(stderr, "cd : HOME not set\n");
			return (free(home) , 1);
		}
	}
	if (chdir(home) == -1)
		perror("chdir()");
	return (free(home), 1);
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

int	builtin_exit(t_data *data, t_execom *execom)
{
	close(execom->fdstdin);
	close(execom->fdstdout);
	printf("exit\n");
	exit_clean(data, NOTHING, Y_EXIT);
	return (1);
}

int	builtin_env(t_data *data)
{
	t_env	*lst;

	lst = data->my_env;
	while (lst != NULL)
	{
		printf("%s\n", lst->line);
		lst = lst->next;
	}
	return (1);
}
