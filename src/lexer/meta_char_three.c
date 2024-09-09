/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:32:08 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/09 16:51:31 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_file_tk(t_token *first)
{
	t_token	*lst;

	lst = first;
	while (lst != NULL)
	{
		if ((is_redirection(lst->type) == 1 && lst->next != NULL
				&& is_str_sq_dq_dol(lst->next->type) == 1)
			&& lst->next->type == DOLLAR_FAIL)
		{
			lst = lst->next;
			lst->type = FILE_TOKEN;
		}
		lst = lst->next;
	}
}
