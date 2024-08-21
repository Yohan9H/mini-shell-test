/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:10:54 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/21 14:48:45 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verif_nothing(t_data *data, t_token *lst)
{
	if (lst->next == NULL)
	{
		fprintf(stderr, "error : nothing after \'%s\'\n", lst->value);
		exit_clean(data, NOTHING, N_EXIT);
	}
}

void	verif_same_tk(t_data *data, t_token *lst, tokentype type)
{
	if (lst->type == type)
	{
		fprintf(stderr, "error near unexpected token \'%s\'\n", lst->value);
		exit_clean(data, NOTHING, N_EXIT);
	}
}

void	verif_redirection_pipe(t_data *data, t_token *lst)
{
	if (is_redirection(lst->type) == 1)
	{
		fprintf(stderr, "error near unexpected token \'%s\'\n", lst->value);
		exit_clean(data, NOTHING, N_EXIT);
	}
	if (data->code_reset == 0 && lst->type == PIPE_TOKEN)
	{
		fprintf(stderr, "error near unexpected token \'|\'\n");
		exit_clean(data, NOTHING, N_EXIT);
	}
}
