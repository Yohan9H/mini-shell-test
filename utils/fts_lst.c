/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:56:19 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/23 12:01:12 by yohurteb         ###   ########.fr       */
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
	if (del->type == STRING_TOKEN)
		free(del->value);
	free(del);
	del = NULL;
}
