/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:09:22 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/30 11:15:02 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
# define COMMAND_NOT_FOUND 127
# define IS_A_DIRECTORY 126

typedef struct s_execom
{
	int			pipe_fd[2];
	int			prev_fd;
	int			fdstdin;
	int			fdstdout;
}	t_execom;

//void	error_exec(t_data *data, char *path, int error_nb);

void	error_exec(char *path, int error_nb);

void	dup2_clean(int in, int out);

int		is_builtin(t_data *data, t_exec *lst);

void	dup2_clean(int in, int out);

void	init_fd(int input_test, t_execom *execom);

void	wait_children(t_data *data);

void	init_pipes(t_execom *execom, t_data *data);

void	close_fds(t_execom *execom);

void	child_process(t_exec *exec,	t_data *data, t_execom *execom);

int		create_child_process(t_data *data);

int		open_clean(t_redir *redir, t_data *data, t_execom *execom);

int		exec_line(t_exec *exec, t_data *data);

void	redir(t_redir *redir, t_data *data, t_execom *execom);

int		input_redir(t_redir *redir);

int		output_redir(t_redir *redir);

int		is_absolute_path(char *cmd);

void	total_unlink(t_data *data);

#endif