/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:43:49 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/21 12:14:55 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_string(char *str, t_data *data, int *i)
{
	int len;

	if (str[*i] != ' ')
	{
		len = len_string(str, i);
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			exit_clean(data, MALLOC, Y_EXIT);
		cpy_str(str, data, i, ' ');
		data->lex->new = ft_lstnew(data->lex->string, STRING_TOKEN, data);
		return (1);
	}
	return (0);
}

void	add_file_tk(t_token *first)
{
	t_token	*lst;

	lst = first;
	while (lst != NULL)
	{
		if (is_redirection(lst->type) == 1 && lst->next != NULL
			&& lst->next->type == STRING_TOKEN)
		{
			lst = lst->next;
			lst->type = FILE_TOKEN;
		}
		lst = lst->next;
	}
}