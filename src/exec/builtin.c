/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:24:21 by apernot           #+#    #+#             */
/*   Updated: 2024/09/17 17:40:05 by yohurteb         ###   ########.fr       */
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
		ft_fprintf("cd : too many arguments\n");
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
			ft_fprintf("cd : HOME not set\n");
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

int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_data *data, char **args, t_execom *execom)
{
	unsigned char	para;

	printf("exit\n");
	if (args[1])
	{
		para = ft_atoi(args[1]);
		if (args[2] != NULL)
		{
			data->exit_code = 1;
			ft_fprintf("%s: too many arguments\n", args[0]);
			return (1);
		}
		if (!(is_numeric(args[1])))
		{
			data->exit_code = 2;
			ft_fprintf("%s: numeric argument required\n", args[1]);
		}
	}
	data->exit_code = para;
	close(execom->fdstdin);
	close(execom->fdstdout);
	exit_clean(data, NOTHING, Y_EXIT);
}

int	builtin_env(t_data *data, char **args)
{
	t_env	*lst;

	lst = data->my_env;
	if (args[1])
	{
		data->exit_code = 127;
		ft_fprintf("\'%s\': No such file or directory\n", args[1]);
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
