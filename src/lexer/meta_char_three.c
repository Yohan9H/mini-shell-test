/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:32:08 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/17 10:20:17 by yohurteb         ###   ########.fr       */
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
				&& is_str_sq_dq_dol(lst->next->type) == 1))
		{
			lst = lst->next;
			lst->type = FILE_TOKEN;
		}
		lst = lst->next;
	}
}

int	verif_edge_case(char *str, int *i, t_data *data)
{
	if (str[*i + 1] == ' ' || str[*i + 1] == '\0')
	{
		data->lex->string = ft_strdup("$");
		data->lex->new = ft_lstnew(data->lex->string, DOLLAR_TOKEN, data);
		(*i)++;
		return (1);
	}
	if (str[*i + 1] == '?')
	{
		data->lex->string = ft_itoa(data->exit_code);
		data->lex->new = ft_lstnew(data->lex->string, DOLLAR_TOKEN, data);
		*i = *i + 2;
		return (1);
	}
	return (0);
}
