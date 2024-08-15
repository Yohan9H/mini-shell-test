/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:20:40 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/15 14:57:48 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front(t_token **lst, t_token *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	(*lst)->prev = new;
	*lst = new;
}

// int	main()
// {
// 	t_list	*lst;
// 	t_list	new;

// 	ft_lstadd_front(&lst, &new);
// 	return (0);
// }