/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:09:38 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/10 13:56:20 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_n(char *args)
{
	int		i;

	i = 0;
	if (!args)
		return (-1);
	if (args[i] && args[i] == '-')
	{
		i++;
		while (args[i] && args[i] == 'n')
			i++;
		if (!args[i])
			return (1);
	}
	return (0);
}

int	verif_if_dollar_sq(char *target, t_data *data, int len)
{
	t_env	*lst_env;
	int		j;

	j = 0;
	lst_env = data->my_env;
	while (lst_env != NULL)
	{
		if (ft_strncmp(lst_env->line, target, len) == 0
			&& lst_env->line[len] == '=')
				return (1);
		lst_env = lst_env->next;
	}
	return (0);
}

void	condition_of_print(t_data *data, char **args, int *i)
{
	int		len;

	if (args[*i][0] == '$')
	{
		len = ft_strlen(&args[*i][1]);
		if (verif_if_dollar_sq(&args[*i][1], data, len) == 1
			|| args[*i][1] == '\0' || args[*i][1] == ' ')
		{
			if (args[*i + 1] == NULL)
				printf("%s", args[*i]);
			else
				printf("%s ", args[*i]);
		}
	}
	else if (args[*i][0] != '$')
	{
		if (args[*i + 1] == NULL)
			printf("%s", args[*i]);
		else
			printf("%s ", args[*i]);
	}
}

int	builtin_echo(t_data *data, char **args)
{
	char	*tmp;
	int		param;
	int		i;

	i = 1;
	param = verif_n(args[i]);
	if (param == 1)
		i++;
	while (args[i] && verif_n(args[i]) != 0)
		i++;
	while (args[i])
	{
		condition_of_print(data, args, &i);
		i++;
	}
	if (param == 0 || args[1] == NULL)
		printf("\n");
	return (1);
}
