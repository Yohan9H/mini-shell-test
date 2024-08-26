/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:43:49 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/26 17:15:55 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space(char *str, t_data *data, int *i)
{
	if (is_allspace(str[*i]) == 1)
	{
		while (is_allspace(str[*i]) == 1)
			(*i)++;
		data->lex->new = ft_lstnew(NULL, SPACE_TK, data);
		return (1);
	}
	else
		return (0);
}

int	is_string(char *str, t_data *data, int *i)
{
	int len;

	if (str[*i] && is_allspace(str[*i]) == 0 && is_metachar(str[*i]) == 0)
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

int	get_value(char *target, t_data *data, int len)
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
		return (1);
	else
		return (0);
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
		if (get_value(data->lex->string, data, len) == 1)
			return (0);
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
