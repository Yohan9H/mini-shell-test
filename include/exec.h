/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:09:22 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/12 17:06:01 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
# define COMMAND_NOT_FOUND 126
# define IS_A_DIRECTORY 127

typedef struct s_execom
{
	int			pipe_fd[2];
	int			prev_fd;
	int			fdstdin;
	int			fdstdout;
}	t_execom;

void	error_exec(char *path, int error_nb);

void	dup2_clean(int in, int out);

int		is_builtin(t_data *data, t_exec *lst);

#endif