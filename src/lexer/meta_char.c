/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:12:58 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/22 15:23:51 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_redirection(char *str, t_data *data, int *i)
{
	if (str[*i + 1] && ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<')))
	{
		if (str[*i] == '>')
			data->lex->new = ft_lstnew(">>", APPEND_TOKEN, data);
		else
			data->lex->new = ft_lstnew("<<", HEREDOC_TOKEN, data);
		return (1);
	}
	return (0);
}

int	single_redirection(char *str, t_data *data, int *i)
{
	if ((str[*i] == '>' || str[*i] == '<'))
	{
		if (str[*i] == '>')
			data->lex->new = ft_lstnew(">", OUTPUT_TOKEN, data);
		else
			data->lex->new = ft_lstnew("<", INPUT_TOKEN, data);
		return (1);
	}
	return (0);
}

int	check_pipe(char *str, t_data *data, int *i)
{
	if (str[*i] == '|')
	{
		data->lex->new = ft_lstnew("|", PIPE_TOKEN, data);
		return (1);
	}
	return (0);
}

int	double_quote(char *str, t_data *data, int *i)
{
	int	len;

	if (str[*i] == '"')
	{
		len = len_db_quote(str, i, '"');
		if (verif_sep_close(str, i, DOUBLE_Q, len) == 1)
			return (exit_clean(data, QUOTE_CLOSE, N_EXIT), 0);
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			exit_clean(data, MALLOC, N_EXIT);
		cpy_str(str, data, i, '"');
		data->lex->new = ft_lstnew(data->lex->string, DQ_TOKEN, data);
		return (1);
	}
	return (0);
}

int	single_quote(char *str, t_data *data, int *i)
{
	int	len;

	if (str[*i] == '\'')
	{
		len = len_db_quote(str, i, '\'');
		if (verif_sep_close(str, i, SINGLE_Q, len) == 1)
			return (exit_clean(data, QUOTE_CLOSE, N_EXIT), 0);
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			exit_clean(data, MALLOC, N_EXIT);
		cpy_str(str, data, i, '\'');
		data->lex->new = ft_lstnew(data->lex->string, SQ_TOKEN, data);
		return (1);
	}
	return (0);
}
