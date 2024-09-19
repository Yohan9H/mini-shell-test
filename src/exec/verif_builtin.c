/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:03:31 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/19 16:45:34 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_builtin(t_data *data, t_exec *lst, t_execom *execom)
{
	if (!lst->cmd)
		return (0);
	if (ft_strncmp("cd", lst->cmd, 3) == 0)
		return (builtin_cd(data, lst->args));
	else if (ft_strncmp("pwd", lst->cmd, 4) == 0)
		return (builtin_pwd(data));
	else if (ft_strncmp("exit", lst->cmd, 5) == 0)
		return (builtin_exit(data, lst->args, execom));
	else if (ft_strncmp("env", lst->cmd, 4) == 0)
		return (builtin_env(data, lst->args));
	else if (ft_strncmp("unset", lst->cmd, 6) == 0)
		return (builtin_unset(data, lst->args));
	else if (ft_strncmp("export", lst->cmd, 7) == 0)
		return (builtin_export(data, lst->args));
	else if (ft_strncmp("echo", lst->cmd, 5) == 0)
		return (builtin_echo(data, lst->args));
	else
		return (0);
	(void)data;
}

int	is_builtin(t_data *data, t_exec *lst)
{
	if (!lst->cmd)
		return (0);
	if (ft_strncmp("cd", lst->cmd, 3) == 0)
		return (1);
	else if (ft_strncmp("pwd", lst->cmd, 4) == 0)
		return (1);
	else if (ft_strncmp("exit", lst->cmd, 5) == 0)
		return (1);
	else if (ft_strncmp("env", lst->cmd, 4) == 0)
		return (1);
	else if (ft_strncmp("unset", lst->cmd, 6) == 0)
		return (1);
	else if (ft_strncmp("export", lst->cmd, 7) == 0)
		return (1);
	else if (ft_strncmp("echo", lst->cmd, 5) == 0)
		return (1);
	else
		return (0);
	(void)data;
}