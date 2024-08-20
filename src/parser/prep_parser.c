/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:01:44 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/20 10:20:43 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_file_tk(t_token *first)
{
	t_token	*lst;

	lst = first;
	while (lst != NULL)
	{
		if (is_redirection(lst->type) == 1 && lst->next != NULL)
		{
			lst = lst->next;
			lst->type = FILE_TOKEN;
		}
		lst = lst->next;
	}
}

void	prep_parser(t_data *data)
{
	add_file_tk(data->lex->first);
}

























// ------------------- TRY --------------------











// void	modif_str_tk(t_token *first)
// {
// 	t_token	*lst;

// 	lst = first;
// 	if (is_str_sg_db(lst->type) == 1)
// 		lst->type = COMMAND_TOKEN;
// 	while (lst->next != NULL)
// 	{
// 		if (lst->type == PIPE_TOKEN)
// 		{
// 			lst = lst->next;
// 			if (is_str_sg_db(lst->type) == 1)
// 				lst->type = COMMAND_TOKEN;
// 		}
// 		else
// 			lst = lst->next;
// 	}
// }

// void	add_arg(t_token *first)
// {
// 	t_token	*lst;

// 	lst = first;
// 	while (lst->next != NULL)
// 	{
// 		if (is_str_sg_db(lst->type) == 1)
// 		{
// 			lst = lst->next;
// 			if (lst->type == STRING_TOKEN)
// 				lst->type = ARG_TOKEN;
// 		}
// 		else
// 			lst = lst->next;
// 	}
// }