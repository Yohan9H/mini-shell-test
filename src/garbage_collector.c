/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:56:23 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/16 18:28:09 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error)
{
	if (error == MALLOC)
		fprintf(stderr, "error malloc\n");
	if (error == QUOTE_CLOSE)
		fprintf(stderr, "error quote\n");
}

void	exit_clean(t_data *data, type_error error, bool num)
{
	if (data->lex->first)
	{
		ft_lstclear(&(data->lex->first));
		data->lex->first = NULL;
	}
	if (data->lex->input)
	{
		free(data->lex->input);
		data->lex->input = NULL;
	}
	if (data->lex->new)
	{
		free(data->lex->new);
		data->lex->new = NULL;
	}
	print_error(error);
	if (num == Y_EXIT)
		exit(1);
	else if (num == N_EXIT)
		data->lex->input = NULL;
	else
		return ;
}
