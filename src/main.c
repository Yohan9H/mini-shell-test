/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:28:39 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/02 16:24:43 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	init_sig();
	while (1)
	{
		lexer(&data);
		if (data.code_reset == 0)
			parser(&data);
		if (data.code_reset == 0)
			exec_cmd(&data, env);
		if (data.code_reset == 0)
			test_minishell(&data);
		exit_clean(&data, NOTHING, N_EXIT);
	}
	// free data->lex
}
