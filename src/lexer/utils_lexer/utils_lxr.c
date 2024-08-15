/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lxr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:17:37 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/15 17:25:16 by yohurteb         ###   ########.fr       */
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

int	len_string(char *str, int *i)
{
	int	len;
	int tmp;

	len = 0;
	tmp = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '"' && str[*i] != '\'')
	{
		(*i)++;
		len++;
	}
	*i = tmp;
	return (len);
}

int if_stop(char *str, t_data *data, int *i, char stop)
{
	if (stop == STRING)
		if (str[*i] == DOUBLE_Q || str[*i] == SINGLE_Q)
			return (1);
	if ((stop == DOUBLE_Q || stop == SINGLE_Q) 
		&& (str[*i] == DOUBLE_Q || str[*i] == SINGLE_Q))
	{
		(data->lex->nb_sep)--;
		printf("lex->nb_sep = %d\n", data->lex->nb_sep); // test
		if (data->lex->nb_sep == 0)
			return (1);
	}
	return (0);
}

void	cpy_str(char *str, t_data *data, int *i, char stop)
{
	int tmp;

	tmp = 0;
	while (str[*i] && str[*i] != stop)
	{
		data->lex->string[tmp] = str[*i];
		(*i)++;
		tmp++;
		if (if_stop(str, data, i, stop) == 1)
			break;
	}
	if (!str[*i] && stop != STRING)
		(*i)--;
	// if (stop == DOUBLE_Q || stop == SINGLE_Q) Ne fonctionne pas
	// 	if (str[*i - 1] != stop)
	// 		exit_clean(data, END_QUOTE);
	data->lex->string[tmp] = '\0';
}

int	verif_sep(char *str, int *i)
{
	int	tmp;
	int	nb_sep;

	tmp = *i;
	nb_sep = 0;
	while (str[*i] && str[*i] != STRING)
	{
		if (str[*i] == DOUBLE_Q || str[*i] == SINGLE_Q)
			nb_sep++;
		(*i)++;
	}
	*i = tmp;
	printf("nb_sep = %d\n", nb_sep);
	return (nb_sep);
}
