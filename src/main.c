/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:28:39 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/31 15:13:06 by yohurteb         ###   ########.fr       */
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
		//if (data.code_reset == 0)
		//	exec();
		if (data.code_reset == 0)
			test_minishell(&data);
		exit_clean(&data, NOTHING, N_EXIT);
	}
	// free data->lex
}
