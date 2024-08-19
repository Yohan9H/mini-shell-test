/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:01:44 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/19 16:53:07 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Pas utile a supp 

void	modif_str_tk(t_token *first)
{
	t_token	*lst;

	lst = first;
	if (is_str_sg_db(lst->type) == 1)
		lst->type = COMMAND_TOKEN;
	while (lst->next != NULL)
	{
		if (lst->type == PIPE_TOKEN)
		{
			lst = lst->next;
			if (is_str_sg_db(lst->type) == 1)
				lst->type = COMMAND_TOKEN;
		}
		else
			lst = lst->next;
	}
}

void	add_arg(t_token *first)
{
	t_token	*lst;

	lst = first;
	while (lst->next != NULL)
	{
		if (is_str_sg_db(lst->type) == 1)
		{
			lst = lst->next;
			if (lst->type == STRING_TOKEN)
				lst->type = ARG_TOKEN;
		}
		else
			lst = lst->next;
	}
}

void	prep_parser(t_data *data)
{
	add_arg(data->lex->first);
	modif_str_tk(data->lex->first);
}