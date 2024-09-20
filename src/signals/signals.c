/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:12:23 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/20 13:39:44 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var_global = 0;
int g_ctrl_c_received = 0;


void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var_global = 1;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
	g_ctrl_c_received = 1;
}



void	init_sig(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
