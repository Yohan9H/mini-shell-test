/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:56:23 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/12 18:41:37 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini-shell.h"

void	print_error(int error)
{
	if (error == MALLOC)
		fprintf(stderr, "error malloc");
}

void	exit_clean(t_data *data, int error)
{
	if (data->lex->first)
		ft_lstclear(&(data->lex->first));
	if (data->lex->input)
		free(data->lex->input);
	if (data->lex->new)
		free(data->lex->new);
	print_error(error);
	exit(1);
}
