/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:24:21 by apernot           #+#    #+#             */
/*   Updated: 2024/09/19 13:51:13 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_nb_parameter(char **args, t_data *data)
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
	{
		ft_fprintf("minishell: cd: too many arguments\n");
		data->exit_code	= 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(t_data *data, char **args)
{
	char	*home;

	if (verif_nb_parameter(args, data) == 1)
		return (1);
	home = ft_strdup(args[1]);
	if (args[1] == NULL || args[1][0] == '\0')
	{
		free(home);
		home = give_value_env("HOME", data, 4);
		if (home == NULL)
		{
			ft_fprintf("minishell: cd: HOME not set\n");
			data->exit_code = 1;
			return (free(home), 1);
		}
	}
	if (chdir(home) == -1)
	{
		perror("chdir()");
		data->exit_code = 1;
	}
	else
		data->exit_code = 0;
	return (free(home), 1);
}

int	builtin_env(t_data *data, char **args)
{
	t_env	*lst;

	lst = data->my_env;
	if (args[1])
	{
		data->exit_code = 127;
		ft_fprintf("env: \'%s\': No such file or directory\n", args[1]);
		return (1);
	}
	while (lst != NULL)
	{
		printf("%s\n", lst->line);
		lst = lst->next;
	}
	data->exit_code = 0;
	return (1);
}
