/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:51:04 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/19 15:24:56 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new, t_token *last)
{
	t_token	*ptr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->prev = NULL;
		return ;
	}
	ptr = ft_lstlast(*lst);
	ptr->next = new;
	new->prev = ptr;
	last = new;
}
