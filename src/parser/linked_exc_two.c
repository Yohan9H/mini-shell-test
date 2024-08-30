/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_exc_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:58:00 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/30 18:56:03 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_node_redir(t_data *data, t_token *lst, tokentype type)
{
	t_redir *new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		exit_clean(data, MALLOC, Y_EXIT);
	new->filename = ft_strdup(lst->next->value);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_redir	*create_linked_lst_redir(t_data *data, t_token *l_lex)
{
	t_token	*lst;

	lst = l_lex;
	while (lst != NULL && lst->type != PIPE_TK)
	{
		if (is_redirection(lst->type) == 1)
		{
			data->par->new_redir = new_node_redir(data, lst, lst->type);
			ft_rediradd_back(&data->par->fst_rdr, data->par->new_redir);
			data->par->new_redir = NULL;
		}
		lst = lst->next;
	}
	data->par->new_redir = NULL;
	return (data->par->fst_rdr);
}
