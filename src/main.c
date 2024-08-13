/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:28:39 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/13 15:31:12 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini-shell.h"

void	init_data(t_data *data)
{
	data->lex = malloc(sizeof(t_lex));
	data->lex->input = NULL;
	data->lex->first = NULL;
	data->lex->last = NULL;
	data->lex->new = NULL;
	data->lex->string = NULL;
}

int	main()
{
	t_data	data;

	init_data(&data);
	while (1)
	{
		lexer(&data);
		//parseur
		//exec
	}
	free(data.lex);
}
