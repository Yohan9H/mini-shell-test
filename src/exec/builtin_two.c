/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:28:12 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/09 16:10:05 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_data *data, char **delete_var)
{
	t_env	*lst;
	t_env	*tmp;
	int		j;

	j = 1;
	lst = data->my_env;
	if (!delete_var)
		return (1);
	while (delete_var[j])
	{
		while (lst != NULL)
		{
			if (ft_strncmp(lst->line, delete_var[j],
					ft_strlen(delete_var[j])) == 0)
			{
				tmp = lst->next;
				delete_node_env(lst, data);
				lst = tmp;
			}
			else
				lst = lst->next;
		}
		lst = data->my_env;
		j++;
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

void	make_new_var(t_data *data, char **var, int *j, int *i)
{
	t_env	*node;
	char	*value_var;
	char	*final_line;
	char	*name;

	final_line = NULL;
	name = ft_strdup_env(var[*j]);
	if (skip_name(var[*j], i, name) == 1)
	{
		value_var = ft_strdup(&var[*j][*i]);
		final_line = ft_strjoin(name, value_var);
		free(name);
		free(value_var);
		node = create_node_env(data, final_line);
		ft_envadd_back(&data->my_env, node);
		free(final_line);
	}
	else
		free(name);
}

int	builtin_export(t_data *data, char **add_var)
{
	int		i;
	int		j;

	j = 1;
	if (!add_var)
		return (1);
	while (add_var[j])
	{
		i = 0;
		make_new_var(data, add_var, &j, &i);
		j++;
	}
	return (1);
}
