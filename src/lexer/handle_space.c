/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:39:23 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/26 13:28:03 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_sq_dq_dol(tokentype type)
{
	if (type == STRING_TOKEN || type == DQ_TOKEN || type == SQ_TOKEN
		|| type == DOLLAR_TOKEN)
		return (1);
	else
		return (0);
}

void	join_lst(t_token *next, t_token *cur)
{
	cur->value = ft_strjoin(next->value, cur->value);
	cur->type = STRING_TOKEN;
}

void	join_if_no_space(t_data *data)
{
	t_token *lst;

	lst = data->lex->first;
	while (lst != NULL)
	{
		if (lst->next != NULL && is_str_sq_dq_dol(lst->type) == 1
			&& is_str_sq_dq_dol(lst->next->type) == 1)
		{
			join_lst(lst, lst->next);
			delete_node(lst, data);
			lst = data->lex->first;
		}
		else
			lst = lst->next;
	}
}
