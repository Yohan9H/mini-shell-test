/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:54:53 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/31 14:50:22 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef struct s_exec t_exec;

typedef struct s_redir t_redir;

struct s_redir
{
	char		*filename;
	tokentype	type;
	t_redir 	*next;
};

struct s_exec
{
	char	*cmd;
	char	**args;
	t_redir	*redir;
	t_exec	*next;
};

typedef struct s_data_ex
{
	t_exec	*first;
	t_exec	*new;
	t_redir	*new_redir;
}	t_data_ex;

// ---- PARSER ----
void	parser(t_data *data);

void	state_pipe(t_data *data, t_token *lst);

void	state_redirection(t_data *data, t_token *lst);

void	create_linked_lst_exec(t_data *data);

t_redir	*create_linked_lst_redir(t_data *data, t_token *l_lex);

// ---- VERIF STATE ----
void	verif_nothing(t_data *data, t_token *lst);

void	verif_same_tk(t_data *data, t_token *lst, tokentype type);

void	verif_redirection_pipe(t_data *data, t_token *lst);

void	verif_dollar_fail(t_token *next);

// ---- UTILS PARSER ----
int		is_redirection(tokentype type);

#endif