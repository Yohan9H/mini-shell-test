/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:39:05 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/12 14:09:55 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini-shell.h"

t_token	*ft_lstnew(char *value, tokentype token)
{
	t_token	*list;

	list = (t_token *)malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->value = value;
	list->type = token;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

// #include <stdio.h>
// int	main()
// {
// 	char 	content[] = "lorem ipsum dolor sit";
// 	t_list	*lst;

// 	lst = ft_lstnew(content);
// 	printf("Test 1 : %s\n", (char *)lst->content);
// 	free(lst);
// 	return (0);
// }