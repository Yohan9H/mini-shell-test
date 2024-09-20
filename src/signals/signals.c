/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:12:23 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/20 15:51:16 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var_global = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var_global = 1;
}

int	event_hook(void)
{
	if (g_var_global == 1)
		rl_done = 1;
	return (0);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_var_global = 1;
}

void	init_sig(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
