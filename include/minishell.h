/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:30:42 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/04 13:16:15 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "lexer.h"
# include "parser.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h> 

typedef enum
{
	MALLOC,
	QUOTE_CLOSE,
	NOTHING,
} type_error;

typedef struct s_data
{
	t_lex		*lex;
	t_data_ex	*par;
	t_exec		*head;
	int			code_reset;
	char		**my_env;
}	t_data;

typedef struct s_pipe
{
	int			pipe_fd[2];
	int			prev_fd;
}	t_pipe;

//	---- MAIN ----
void	init_data(t_data *data, char **env);

void	print_error(int error);

void	exit_clean(t_data *data, type_error error, bool num);

//  ---- SIGNALS ---- 
void	init_sig();

//	---- UTILS ----
void	ft_lstadd_back(t_token **lst, t_token *new, t_token *last);

void	ft_rediradd_back(t_redir **lst, t_redir *new);

void	ft_execadd_back(t_exec **lst, t_exec *new);

void	ft_lstadd_front(t_token **lst, t_token *new);

void	ft_lstclear(t_token **lst);

void	ft_lstclear_redir(t_redir **lst);

void	ft_lstclear_exec(t_exec **lst);

t_token	*ft_lstlast(t_token *lst);

t_redir	*ft_lstredirlast(t_redir *lst);

t_exec	*ft_lstexeclast(t_exec *lst);

t_token	*ft_lstnew(char *value, tokentype token, t_data *data);

int		ft_lstsize(t_token *lst);

char	**ft_split(char const *s, char c);

int		ft_strlen(const char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strdup(const char *s1);

char	*ft_strjoin(const char *s1, const char *s2);

void	delete_node(t_token *del, t_data *data);

//  ---- EXEC ----
char	*my_get_path(char *cmd, char **envp);

int	exec_cmd(t_data *data, char **envp);

//	---- TEST ----
void	test_minishell(t_data *data);

#endif