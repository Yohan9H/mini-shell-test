/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:51:04 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/12 14:14:00 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini-shell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast(*lst);
	ptr->next = new;
	new->prev = ptr;
}
