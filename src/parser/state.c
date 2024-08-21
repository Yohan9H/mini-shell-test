/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:06:40 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/20 17:31:57 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	state_input(t_token *lst)
{
	if (lst->next == NULL)
		//error();
	if (lst->next->type == PIPE_TOKEN)
		//error();
}