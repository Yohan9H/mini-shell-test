/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:12:58 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/13 17:49:31 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini-shell.h"

int	double_redirection(char *str, t_data *data, int *i)
{
	if (str[*i + 1] && ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<')))
	{
		if (str[*i] == '>')
			data->lex->new = ft_lstnew(">>", REDIRECTION_TOKEN, data);
		else
			data->lex->new = ft_lstnew("<<", REDIRECTION_TOKEN, data);
		return (1);
	}
	return (0);
}

int	single_redirection(char *str, t_data *data, int *i)
{
	if ((str[*i] == '>' || str[*i] == '<'))
	{
		if (str[*i] == '>')
			data->lex->new = ft_lstnew(">", REDIRECTION_TOKEN, data);
		else
			data->lex->new = ft_lstnew("<", REDIRECTION_TOKEN, data);
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

// il faut gerer les cas ou il y a encore des " ", 
// peut etre rappeler la meme fonction une nouvelle fois
int	double_quote(char *str, t_data *data, int *i)
{
	int	len;

	if (str[*i] == '"')
	{
		len = len_db_quote(str, i, '"');
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			exit_clean(data, MALLOC);
		cpy_str(str, data, i, '"');
		data->lex->new = ft_lstnew(data->lex->string, STRING_TOKEN, data);
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
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			exit_clean(data, MALLOC);
		cpy_str(str, data, i, '\'');
		data->lex->new = ft_lstnew(data->lex->string, STRING_TOKEN, data);
		return (1);
	}
	return (0);
}
