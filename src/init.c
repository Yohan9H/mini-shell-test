/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:10:48 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/12 15:16:34 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **env)
{
	data->lex = malloc(sizeof(t_lex));
	if (!data->lex)
		exit_clean(data, MALLOC, Y_EXIT);
	data->lex->input = NULL;
	data->lex->first = NULL;
	data->lex->last = NULL;
	data->lex->new = NULL;
	data->lex->string = NULL;
	data->par = (t_data_ex *)malloc(1 * sizeof(t_data_ex));
	if (!data->lex)
		exit_clean(data, MALLOC, Y_EXIT);
	data->par->first = NULL;
	data->par->new = NULL;
	data->par->new_redir = NULL;
	data->head = NULL;
	data->my_env = NULL;
	data->exit_code = 0;
	create_linked_env(data, env);
}
