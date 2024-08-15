/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:32:43 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/15 14:57:50 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->type == STRING_TOKEN)
			free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

// void	del(void * data)
// {
// 	free(data);
// }
//
// #include <stdio.h>
// int	main()
// {
// 	t_list	*lst_1;
//
//     lst_1 = (t_list *)malloc(sizeof(t_list));
//
// 	lst_1->content = ft_strdup("salut");
// 	lst_1->next = NULL;

// 	ft_lstclear(&lst_1, &del);
// 	if (lst_1 == NULL)
// 		printf("GOOD !\n");
// 	free(lst_1);
// 	return (0);
// }