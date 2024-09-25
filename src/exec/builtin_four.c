/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:48:52 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/25 12:18:39 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	verif_error(t_data *data, char **args, int *not_num)
{
	int		len;

	len = 0;
	while (args[1][len])
		len++;
	if (!(is_numeric(args[1])) || len >= 20)
	{
		*not_num = 1;
		ft_fprintf("minishell: %s: numeric argument required\n", args[1]);
	}
	else if (args[2] != NULL)
	{
		data->exit_code = 1;
		ft_fprintf("minishell: %s: too many arguments\n", args[0]);
		return (1);
	}
	return (0);
}

int	builtin_exit(t_data *data, char **args, t_execom *execom)
{
	unsigned char	para;
	int				not_num;

	not_num = 0;
	para = data->exit_code;
	if (args[1])
		para = ft_atoi(args[1]);
	printf("exit\n");
	if (args[1])
		if (verif_error(data, args, &not_num) == 1)
			return (1);
	close(execom->fdstdin);
	close(execom->fdstdout);
	exit_clean(data, NOTHING, C_EXIT);
	if (not_num == 1)
		exit (2);
	exit (para);
}

int	verif_export_long(t_data *data, char *new, int *i, int real_export)
{
	while (real_export == 1 && new[*i] && new[*i] != '=')
	{
		if (ft_isnum((int)new[*i]) == 1)
		{
			ft_fprintf("minishell: `%s': not a valid identifier\n", new);
			data->exit_code = 1;
			return (1);
		}
		(*i)++;
	}
	*i = 0;
	while (real_export == 0 && new[*i])
	{
		if (ft_isnum((int)new[*i]) == 1)
		{
			ft_fprintf("minishell: `%s': not a valid identifier\n", new);
			data->exit_code = 1;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	verif_all_num_export(t_data *data, char *new)
{
	int		i;
	int		real_export;

	i = 0;
	real_export = 0;
	if (new[i] == '=')
	{
		ft_fprintf("minishell: `%s': not a valid identifier\n", new);
		data->exit_code = 1;
		return (1);
	}
	while (new[i] && new[i] != '=')
	{
		i++;
		if (new[i] == '=')
			real_export = 1;
	}
	i = 0;
	if (verif_export_long(data, new, &i, real_export) == 1)
		return (1);
	return (0);
}
