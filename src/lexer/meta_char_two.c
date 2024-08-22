/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:43:49 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/22 14:09:20 by yohurteb         ###   ########.fr       */
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
			exit_clean(data, MALLOC, N_EXIT);
		cpy_str(str, data, i, ' ');
		data->lex->new = ft_lstnew(data->lex->string, STRING_TOKEN, data);
		return (1);
	}
	return (0);
}

void	get_value(char *target, t_data *data, int len)
{
	int	j;
	int	find;

	j = 0;
	find = 0;
	while (data->my_env[j])
	{
		if (ft_strncmp(data->my_env[j], target, len) == 0)
		{
			find = 1;
			free(data->lex->string);
			data->lex->string = ft_strdup(&(data->my_env)[j][len + 1]);
			break;
		}
		j++;
	}
	if (find == 0)
		data->lex->string = ft_strjoin("$", data->lex->string);
}

int	is_dollar(char *str, t_data *data, int *i)
{
	int	len;

	if (str[*i] == '$')
	{
		if (str[*i + 1] == ' ')
			return (0);
		(*i)++;
		len = len_string(str, i);
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			exit_clean(data, MALLOC, N_EXIT);
		cpy_str(str, data, i, ' ');
		get_value(data->lex->string, data, len);
		data->lex->new = ft_lstnew(data->lex->string, DOLLAR_TOKEN, data);
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