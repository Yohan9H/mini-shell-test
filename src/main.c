/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:28:39 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/20 15:39:28 by yohurteb         ###   ########.fr       */
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
			exec_cmd(&data);
		exit_clean(&data, NOTHING, N_EXIT);
	}
}
