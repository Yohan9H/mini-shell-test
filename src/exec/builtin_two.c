/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:28:12 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/19 13:45:56 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	condition_for_delete(t_env **lst, char **del, int *j, t_data *data)
{
	t_env	*tmp;
	int		len;

	len = ft_strlen(del[*j]);
	if (len != 0 && ft_strncmp((*lst)->line, del[*j], len) == 0)
	{
		tmp = (*lst)->next;
		delete_node_env(*lst, data);
		(*lst) = tmp;
	}
	else
		(*lst) = (*lst)->next;
}

int	builtin_unset(t_data *data, char **delete_var)
{
	t_env	*lst;
	int		j;

	j = 1;
	lst = data->my_env;
	data->exit_code = 0;
	if (!delete_var)
		return (1);
	while (delete_var[j])
	{
		while (lst != NULL)
			condition_for_delete(&lst, delete_var, &j, data);
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
	delete_if_exist(data, name);
	if (skip_name(var[*j], i, name) == 1)
	{
		if (var[*j][*i + 1] == '\0' || var[*j][*i + 1] == ' ')
			value_var = ft_strdup("=");
		else
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

int	builtin_export(t_data *data, char **new)
{
	int		i;
	int		j;

	j = 1;
	if (!new)
		return (1);
	while (new[j])
	{
		i = 0;
		if (is_allspace(new[j][i]) == 1 || new[j][i] == '=')
		{
			ft_fprintf("minishell: `%s': not a valid identifier\n", new[j]);
			data->exit_code = 1;
			return (1);
		}
		make_new_var(data, new, &j, &i);
		j++;
	}
	data->exit_code = 0;
	return (1);
}
