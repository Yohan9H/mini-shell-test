/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:28:39 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/26 14:21:24 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **env) // le move dans le dossier lexer
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
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	while (1)
	{
		lexer(&data);
		//if (data.code_reset == 0)
			//parser(&data);
		//if (data.code_reset == 0)
		//exec
		if (data.code_reset == 0)
			test_minishell(&data);
	}
	// free data->lex
}
