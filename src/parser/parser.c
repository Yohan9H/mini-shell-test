/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:53:21 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/20 10:27:22 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_data *data, t_token *lst)
{
	(void)data;
	(void)lst;
}

void	parser(t_data *data)
{
	t_token	*lst;

	prep_parser(data);
	lst = data->lex->first;
	while (lst != NULL)
	{
		parsing(data, lst);
		lst = lst->next;
	}
}
