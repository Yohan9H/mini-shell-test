/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:19:30 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/13 15:28:26 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini-shell.h>

void	test_minishell(t_data *data); // Pour test 

void	verif_and_add_back(t_data *data, int *i, int num)
{
	if (!data->lex->new)
		exit_clean(data, MALLOC);
	ft_lstadd_back(&(data->lex->first), data->lex->new, data->lex->last);
	data->lex->new = NULL;
	*i = *i + num;
}

int	choice_token(char *str, t_data *data, int i)
{
	if (double_redirection(str, data, &i) == 1)
		verif_and_add_back(data, &i, 2);
	else if (single_redirection(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
	else if (check_pipe(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
	else if (double_quote(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
	else if (is_string(str, data, &i) == 1)
		verif_and_add_back(data, &i, 1);
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
		i = choice_token(str, data, i);
	test_minishell(data); 			// Pour test
}

char	*lexer(t_data *data)
{
	int	i;

	i = 0;
	data->lex->input = readline("minishell> ");
	if (data->lex->first != NULL)
		ft_lstclear(&(data->lex->first));
	add_token(data);
	return (NULL);
}

void	test_minishell(t_data *data) // Pour test
{
	t_token	*tmp = NULL;

	tmp = data->lex->first;
	printf("  ----  \n");
	while (tmp != NULL)
	{
		printf("value type : %u\n", tmp->type);
		printf("value node : %s\n  ----  \n", tmp->value);
		tmp = tmp->next;
	}
}