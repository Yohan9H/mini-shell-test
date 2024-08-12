/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:19:30 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/12 18:43:53 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini-shell.h>

void	verif_and_add_back(t_data *data, int *i, int num)
{
	if (!data->lex->new)
		exit_clean(data, MALLOC);
	ft_lstadd_back(&(data->lex->first), data->lex->new);
	data->lex->new = NULL;
	*i = *i + num;
}

int	choice_token(char *str, t_data *data, int i)
{
	if (str[i + 1] && ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<')))
	{
		if (str[i] == '>')
			data->lex->new = ft_lstnew(">>", REDIRECTION_TOKEN);
		else
			data->lex->new = ft_lstnew("<<", REDIRECTION_TOKEN);
		verif_and_add_back(data, &i, 2);
	}
	else if (single_redirection(str, data, &i)) // voir si possible de faire un truc comme ca pour reduire
		// le code et voir si mes verifs de malloc sont corrects 
	{
		if (str[i] == '>')
			data->lex->new = ft_lstnew(">", REDIRECTION_TOKEN);
		else
			data->lex->new = ft_lstnew("<", REDIRECTION_TOKEN);
		verif_and_add_back(data, &i, 1);
	}
	else if (str[i] == '|')
	{
		data->lex->new = ft_lstnew("|", PIPE_TOKEN);
		verif_and_add_back(data, &i, 1);
	}
	else
		i++;
	return (i);
}

void	add_token(t_data *data)
{
	char	*str;
	int		i;

	str = data->lex->input;
	i = 0;
	while (str[i])
	{
		i = choice_token(str, data, i);
	}
}

char	*lexer(t_data *data)
{
	int	i;

	i = 0;
	data->lex->input = readline("minishell> ");
	add_token(data);
	return (NULL);
}
