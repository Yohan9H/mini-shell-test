/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:43:49 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/11 18:50:18 by yohurteb         ###   ########.fr       */
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
	int		len;

	if (str[*i] && is_allspace(str[*i]) == 0 && is_metachar(str[*i]) == 0)
	{
		len = len_string(str, i, ' ');
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			return (exit_clean(data, MALLOC, N_EXIT), 0);
		cpy_str(str, data, i, ' ');
		data->lex->new = ft_lstnew(data->lex->string, STRING_TOKEN, data);
		return (1);
	}
	return (0);
}

int	get_value(char *target, t_data *data, int len)
{
	t_env	*lst_env;
	int		find;

	find = 0;
	lst_env = data->my_env;
	while (lst_env != NULL)
	{
		if (ft_strncmp(lst_env->line, target, len) == 0
			&& lst_env->line[len] == '=')
		{
			find = 1;
			free(data->lex->string);
			data->lex->string = ft_strdup(&lst_env->line[len + 1]);
			break ;
		}
		lst_env = lst_env->next;
	}
	if (find == 0)
		return (1);
	else
		return (0);
}

void	verif_value(t_data *data, int len)
{
	char	*svg;

	svg = ft_strdup(data->lex->string);
	if (get_value(data->lex->string, data, len) == 1)
	{
		free(data->lex->string);
		free(svg);
		data->lex->string = ft_strdup("");
		if (data->lex->string == NULL)
			exit_clean(data, MALLOC, N_EXIT);
		data->lex->new = ft_lstnew(data->lex->string, DOLLAR_FAIL, data);
		return ;
	}
	free(svg);
	data->lex->new = ft_lstnew(data->lex->string, DOLLAR_TOKEN, data);
}

int	is_dollar(char *str, t_data *data, int *i)
{
	int		len;

	if (str[*i] == '$')
	{
		if (str[*i + 1] == ' ' || str[*i + 1] == '\0')
		{
			data->lex->string = ft_strdup("$");
			data->lex->new = ft_lstnew(data->lex->string, DOLLAR_TOKEN, data);
			(*i)++;
			return (1);
		}
		if (str[*i + 1] == '"' || str[*i + 1] == '\'')
			return (0);
		(*i)++;
		len = len_string(str, i, '$');
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			return (exit_clean(data, MALLOC, N_EXIT), 0);
		cpy_str(str, data, i, '$');
		verif_value(data, len);
		return (1);
	}
	return (0);
}
