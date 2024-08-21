/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:28:39 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/21 11:34:17 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data) // le move dans le dossier lexer
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
		if (data.code_reset == 0)
			parser(&data);
		//if (data.code_reset == 0)
		//exec
		if (data.code_reset == 0) 
			test_minishell(&data);
	}
	// free data->lex
}
