/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:39:05 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/22 12:07:09 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(char *value, tokentype token, t_data *data)
{
	t_token	*list;

	list = (t_token *)malloc(sizeof(t_token));
	if (!list)
		exit_clean(data, MALLOC, N_EXIT);
	list->value = value;
	list->type = token;
	list->next = NULL;
	list->prev = NULL;
	value = NULL;
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