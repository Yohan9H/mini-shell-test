/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:03:31 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/09 15:42:27 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_builtin(t_data *data, t_exec *lst)
{
	if (ft_strncmp("cd", lst->cmd, 2) == 0)
		return (builtin_cd(data, lst->args[1]));
	else if (ft_strncmp("pwd", lst->cmd, 3) == 0)
		return (builtin_pwd());
	else if (ft_strncmp("exit", lst->cmd, 4) == 0)
		return (builtin_exit(data));
	else if (ft_strncmp("env", lst->cmd, 3) == 0)
		return (builtin_env(data));
	else if (ft_strncmp("unset", lst->cmd, 5) == 0)
		return (builtin_unset(data, lst->args));
	else if (ft_strncmp("export", lst->cmd, 6) == 0)
		return (builtin_export(data, lst->args));
	else if (ft_strncmp("echo", lst->cmd, 4) == 0)
		return (builtin_echo(data, lst->args));
	else
		return (0);
}
