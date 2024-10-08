/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:56:19 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/08 14:04:35 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_token *del, t_data *data)
{
	if (del->prev != NULL)
		del->prev->next = del->next;
	else
		data->lex->first = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (is_str_sq_dq_dol(del->type) == 1 || del->type == DOLLAR_FAIL)
		free(del->value);
	free(del);
	del = NULL;
}

int	line_del_found(t_data *data, t_env *current, t_env *prev)
{
	if (prev == NULL)
	{
		data->my_env = current->next;
		free(current->line);
		free(current);
		return (1);
	}
	else
	{
		prev->next = current->next;
		free(current->line);
		free(current);
		return (1);
	}
}

void	delete_node_env(t_env *del, t_data *data)
{
	t_env	*current;
	t_env	*prev;
	int		len;

	current = data->my_env;
	prev = NULL;
	len = ft_strlen(del->line);
	while (current != NULL)
	{
		if (ft_strncmp(current->line, del->line, len) == 0)
			if (line_del_found(data, current, prev) == 1)
				return ;
		prev = current;
		current = current->next;
	}
}
