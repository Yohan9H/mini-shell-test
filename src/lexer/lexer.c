/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:19:30 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/26 15:09:00 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verif_and_add_back(t_data *data, int *i, int num)
{
	if (!data->lex->new)
		exit_clean(data, MALLOC, N_EXIT);
	ft_lstadd_back(&(data->lex->first), data->lex->new, &data->lex->last);
	data->lex->new = NULL;
	*i = *i + num;
}

int	choice_token(char *str, t_data *data, int i, int *reset)
{
	if (*reset == 0 && check_space(str, data, &i) == 1)
		verif_and_add_back(data, &i, 0);
	else if (*reset == 0 && double_redirection(str, data, &i) == 1)
		verif_and_add_back(data, &i, 2);
	else if (*reset == 0 && single_redirection(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
	else if (*reset == 0 && check_pipe(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
	else if (*reset == 0 && double_quote(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
	else if (*reset == 0 && single_quote(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
	else if (*reset == 0 && is_dollar(str, data, &i) == 1)
		verif_and_add_back(data, &i, 0);
	else if (*reset == 0 && is_string(str, data, &i) == 1)
		verif_and_add_back(data, &i, 0);
	else
		if (*reset == 0 && str[i])
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
		i = choice_token(str, data, i, &(data->code_reset));
		if (data->code_reset == 1)
			break ;
	}
	join_if_no_space_and_del_space_fdoll(data);
	add_file_tk(data->lex->first);
}

void	lexer(t_data *data)
{
	data->code_reset = 0;
	data->lex->input = readline("minishell> ");
	if (data->lex->first != NULL)
		ft_lstclear(&(data->lex->first));
	if (data->lex->input == NULL)
	{
		printf("exit\n");
		exit_clean(data, NOTHING, Y_EXIT);
	}
	if (data->lex->input && data->lex->input[0])
		add_history(data->lex->input);
	if (data->code_reset == 0)
		add_token(data);
}
