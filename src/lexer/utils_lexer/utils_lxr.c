/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lxr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:17:37 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/26 16:27:15 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_db_quote(char *str, int *i, char stop)
{
	int	len;
	int	tmp;

	len = 0;
	(*i)++;
	tmp = *i;
	while (str[*i] && str[*i] != stop)
	{
		(*i)++;
		len++;
	}
	*i = tmp;
	return (len);
}

void	code_dollar_true(char *str, int *i, int *len)
{
	while (str[*i] && is_allspace(str[*i]) != 1
		&& str[*i] != '"' && str[*i] != '\'' && str[*i] != '['
		&& str[*i] != '$' && str[*i] != '<' && str[*i] != '>'
		&& str[*i] != ']')
	{
		(*i)++;
		(*len)++;
	}
}

int	len_string(char *str, int *i, char code)
{
	int		len;
	int		tmp;

	len = 0;
	tmp = *i;
	if (code == '$')
		code_dollar_true(str, i, &len);
	else
	{
		while (str[*i] && is_allspace(str[*i]) != 1
			&& str[*i] != '"' && str[*i] != '\''
			&& str[*i] != '$' && str[*i] != '<' && str[*i] != '>')
		{
			(*i)++;
			len++;
		}
	}
	*i = tmp;
	return (len);
}

void	cpy_str(char *str, t_data *data, int *i, char stop)
{
	int		tmp;

	tmp = 0;
	while (str[*i] && str[*i] != stop)
	{
		data->lex->string[tmp] = str[*i];
		(*i)++;
		tmp++;
		if (stop == STRING)
			if (str[*i] == DOUBLE_Q || str[*i] == SINGLE_Q || str[*i] == '$'
				|| str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
				break ;
		if (stop == '$')
			if (str[*i] == DOUBLE_Q || str[*i] == SINGLE_Q || str[*i] == '$'
				|| str[*i] == '>' || str[*i] == '<' || str[*i] == '|'
				|| str[*i] == '[' || str[*i] == ']' || str[*i] == '/'
				|| str[*i] == ' ')
				break ;
		data->lex->string[tmp] = str[*i];
	}
	if (!str[*i] && stop != STRING && stop != '$')
		(*i)--;
	data->lex->string[tmp] = '\0';
}

int	verif_sep_close(char *str, int *i, char type, int len)
{
	int	tmp;
	int	nb_sep;

	tmp = *i;
	nb_sep = 0;
	while (str[*i] && len > 0 && str[*i] != type)
	{
		(*i)++;
		len--;
	}
	if (str[*i] == type)
		nb_sep++;
	*i = tmp;
	if (nb_sep != 1)
		return (1);
	else
		return (0);
}
