/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:28:12 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/09 11:30:04 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_data *data, char *delete_var)
{
	t_env	*lst;

	lst = data->my_env;
	if (!delete_var)
		return (1);
	while (lst != NULL)
	{
		if (ft_strncmp(lst->line, delete_var, ft_strlen(delete_var)) == 0)
		{
			delete_node_env(lst, data);
			return (1);
		}
		lst = lst->next;
	}
	return (1);
}

int	skip_name(char *add_var, int *i, char *name)
{
	if (name[0] == '\0')
		return (0);
	while (add_var[*i] && add_var[*i] != '=')
		(*i)++;
	if (add_var[*i] == '=')
		if (add_var[*i + 1])
			return (1);
}

int	builtin_export(t_data *data, char *add_var)
{
	t_env	*node;
	char	*name;
	char	*value_var;
	char	*final_line;
	int		i;

	i = 0;
	if (!add_var)
		return (1);
	final_line = NULL;
	name = ft_strdup_env(add_var);
	if (skip_name(add_var, &i, name) == 1)
	{
		value_var = ft_strdup(&add_var[i]);
		final_line = ft_strjoin(name, value_var);
		free(name);
		free(value_var);
		node = create_node_env(data, final_line);
		ft_envadd_back(&data->my_env, node);
		free(final_line);
	}
	else
		free(name);
	return (1);
}

char	*verif_n(t_data *data, char **args)
{
	int	i;
	int	j;

	j = 0;
	while (args[j])
	{
		i = 0;
		while (args[j][i])
		{
			if (args[j][i] == '-')
			{
				i++;
				while (args[j][i] && args[j][i] == 'n')
					i++;
				if (!args[j][i])
					return (args[j]);
			}
			else
				i++;
		}
		j++;
	}
	return (NULL);
}

int	builtin_echo(t_data *data, char **args)
{
	char	*tmp;
	char	*param;
	int		i;

	i = 1;
	param = verif_n(data, args);
	while (args[i])
	{
		if (args[i] == param)
			i++;
		else
		{
			if (args[i + 1] == NULL || (args[i + 1] == param && !args[i + 1]))
				printf("%s", args[i]);
			else
				printf("%s ", args[i]);
			i++;
		}
	}
	if (param == NULL)
		printf("\n");
	return (1);
}
