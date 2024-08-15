/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:56:23 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/15 16:44:32 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error)
{
	if (error == MALLOC)
		fprintf(stderr, "error malloc\n");
	if (error == END_QUOTE)
		fprintf(stderr, "error quote\n");
}

void	exit_clean(t_data *data, type_error error)
{
	if (data->lex->first)
		ft_lstclear(&(data->lex->first));
	if (data->lex->input)
		free(data->lex->input);
	if (data->lex->new)
		free(data->lex->new);
	if (data->lex->string)
		free(data->lex->string);
	print_error(error);
	exit(1);
}
