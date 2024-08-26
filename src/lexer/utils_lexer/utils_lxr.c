/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lxr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:17:37 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/26 14:41:42 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_allspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

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
	while (str[*i] && str[*i] != ' ' && str[*i] != '"' && str[*i] != '\''
		&& str[*i] != '$')
	{
		(*i)++;
		len++;
	}
	*i = tmp;
	return (len);
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
		if (stop == STRING)
			if (str[*i] == DOUBLE_Q || str[*i] == SINGLE_Q || str[*i] == '$')
				break;
	}
	if (!str[*i] && stop != STRING)
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








// ------------------------  TRY  ---------------------------









// int if_stop(char *str, t_data *data, int *i, char stop) // ne fonctionne plus avec ""''""ls""''"" si je fais cette tech pour gere le cas "make""file"
// {													   // essai pour gere la concatenation de 2 str
// 	if ((stop == DOUBLE_Q || stop == SINGLE_Q) 
// 		&& (str[*i] == DOUBLE_Q || str[*i] == SINGLE_Q))
// 	{
// 		(data->lex->nb_sep)--;
// 		printf("lex->nb_sep = %d\n", data->lex->nb_sep); // test
// 		if (data->lex->nb_sep == 1)
// 			return (1);
// 	}
// 	return (0);
// }

// int	condition_cpy(char *str, t_data *data, int *i, char stop) // essai pour gere la concatenation de 2 str
// {
// 	if (stop == STRING)
// 		if (str[*i] == stop)
// 			return (1);
// 	if (stop == DOUBLE_Q || stop == SINGLE_Q)
// 		if (data->lex->nb_sep == 0)
// 			return (1);
// 	return (0);
// }