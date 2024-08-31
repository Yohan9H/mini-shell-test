/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:10:48 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/31 15:11:13 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **env)
{
	data->my_env = env; // methode a changer apres 
	data->lex = malloc(sizeof(t_lex));
	if (!data->lex)
		exit(1);
	data->lex->input = NULL;
	data->lex->first = NULL;
	data->lex->last = NULL;
	data->lex->new = NULL;
	data->lex->string = NULL;
	data->par = (t_data_ex *)malloc(1 * sizeof(t_data_ex));
	data->par->first = NULL;
	data->par->new = NULL;
	data->par->new_redir = NULL;
	data->head = NULL;
}
