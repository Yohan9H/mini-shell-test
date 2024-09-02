/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:53:21 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/31 14:29:23 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verif_first_position(t_data *data, t_token *lst)
{
	if (lst->type == PIPE_TK)
	{
		fprintf(stderr, "error near unexpected token \'|\'\n");
		exit_clean(data, NOTHING, N_EXIT);
	}
}

void	parsing(t_data *data, t_token *lst, int	*reset)
{
	if (*reset == 0 && lst->type == PIPE_TK)
		state_pipe(data, lst);
	if (*reset == 0 && is_redirection(lst->type) == 1)
		state_redirection(data, lst);
}

void	clean_lst(t_token *head)
{
	t_token	*lst;

	lst = head;
	while (lst != NULL)
	{
		if (lst->type == DQ_TOKEN || lst->type == SQ_TOKEN
			|| lst->type == DOLLAR_TOKEN)
			lst->type = STRING_TOKEN;
		lst = lst->next;
	}
}

void	parser(t_data *data)
{
	t_token	*lst;

	if (data->lex->first == NULL)
		return(exit_clean(data, NOTHING, N_EXIT));
	lst = data->lex->first;
	verif_first_position(data, data->lex->first);
	while (data->code_reset == 0 && lst != NULL)
	{
		parsing(data, lst, &data->code_reset);
		if (data->code_reset == 0)
			lst = lst->next;
	}
	if (data->code_reset == 0)
		clean_lst(data->lex->first);
	if (data->code_reset == 0)
		create_linked_lst_exec(data);
	data->head = data->par->first;
}
