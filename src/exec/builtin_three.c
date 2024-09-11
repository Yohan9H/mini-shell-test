/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:09:38 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/11 17:56:27 by yohurteb         ###   ########.fr       */
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

void	condition_of_print(t_data *data, char **args, int *i)
{
	int		len;

	if (args[*i + 1] == NULL)
		printf("%s", args[*i]);
	else
		printf("%s ", args[*i]);
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

void	delete_if_exist(t_data *data, char *name)
{
	int		len;
	t_env	*lst;
	t_env	*tmp;

	lst = data->my_env;
	while (lst != NULL)
	{
		len = ft_strlen(name);
		if (len != 0 && ft_strncmp(lst->line, name, len) == 0)
		{
			tmp = lst->next;
			delete_node_env(lst, data);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
}
