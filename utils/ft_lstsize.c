/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:29:17 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/09 15:55:02 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_token *lst)
{
	t_token	*ptr;
	int		count;

	count = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

int	ft_lstsize_env(t_env *env)
{
	t_env	*ptr;
	int		count;

	count = 0;
	ptr = env;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

// #include <stdio.h>
// int	main()
// {
// 	t_list	*lst_1;
// 	t_list	*lst_2;
// 	t_list	*lst_3;
// 	t_list	*lst_4;

//     lst_1 = (t_list *)malloc(sizeof(t_list));
//     lst_2 = (t_list *)malloc(sizeof(t_list));
//     lst_3 = (t_list *)malloc(sizeof(t_list));
//     lst_4 = (t_list *)malloc(sizeof(t_list));

// 	lst_1->next = lst_2;
// 	lst_2->next = lst_3;
// 	lst_3->next = lst_4;
// 	lst_4->next = NULL;
// 	printf("My function : %d\n", ft_lstsize(lst_1));
// 	free(lst_1);
//     free(lst_2);
//     free(lst_3);
//     free(lst_4);
// 	return (0);
// }