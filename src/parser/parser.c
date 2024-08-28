/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:53:21 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/28 09:07:15 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verif_first_position(t_data *data, t_token *lst)
{
	if (lst->type == PIPE_TOKEN)
	{
		fprintf(stderr, "error near unexpected token \'|\'\n");
		exit_clean(data, NOTHING, N_EXIT);
	}
}

void	parsing(t_data *data, t_token *lst, int	*reset)
{
	if (*reset == 0 && lst->type == PIPE_TOKEN)
		state_pipe(data, lst);
	if (*reset == 0 && is_redirection(lst->type) == 1)
		state_redirection(data, lst);
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
}
