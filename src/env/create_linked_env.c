/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linked_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:08:10 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/08 14:12:29 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node_env(t_data *data, char *line)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		exit_clean(data, NOTHING, N_EXIT);
	node->line = ft_strdup(line);
	node->next = NULL;
	return (node);
}

void	create_linked_env(t_data *data, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		node = create_node_env(data, env[i]);
		ft_envadd_back(&data->my_env, node);
		i++;
	}
}
