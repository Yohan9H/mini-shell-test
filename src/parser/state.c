/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:06:40 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/05 14:36:41 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_pipe(t_data *data, t_token *lst)
{
	verif_nothing(data, lst);
	if (data->code_reset == 0)
		verif_same_tk(data, lst->next, lst->type);
}

void	state_redirection(t_data *data, t_token *lst)
{
	verif_nothing(data, lst);
	if (data->code_reset == 0)
		verif_same_tk(data, lst->next, lst->type);
	if (data->code_reset == 0)
		verif_redirection_pipe(data, lst->next);
}
