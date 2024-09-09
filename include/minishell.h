/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:30:42 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/08 15:59:43 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "lexer.h"
# include "parser.h"
# include "env.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h> 
# include <linux/limits.h>

typedef enum e_type_error
{
	MALLOC,
	QUOTE_CLOSE,
	NOTHING,
	OPEN,
}	t_type_error;

typedef struct s_data
{
	t_lex		*lex;
	t_data_ex	*par;
	t_exec		*head;
	int			code_reset;
	t_env		*my_env;
}	t_data;

typedef struct s_execom
{
	int			pipe_fd[2];
	int			prev_fd;
	int			fdstdin;
	int			fdstdout;
}	t_execom;

//	---- MAIN ----
void	init_data(t_data *data, char **env);

void	print_error(int error);

void	exit_clean(t_data *data, t_type_error error, t_bool num);

//  ---- SIGNALS ---- 
void	init_sig(void);

//	---- UTILS ----
void	ft_lstadd_back(t_token **lst, t_token *new, t_token *last);

void	ft_rediradd_back(t_redir **lst, t_redir *new);

void	ft_execadd_back(t_exec **lst, t_exec *new);

void	ft_envadd_back(t_env **lst, t_env *new);

t_env	*create_node_env(t_data *data, char *line);

void	ft_lstadd_front(t_token **lst, t_token *new);

void	ft_lstclear(t_token **lst);

void	ft_lstclear_redir(t_redir **lst);

void	ft_lstclear_exec(t_exec **lst);

void	ft_lstclear_env(t_env **lst);

t_token	*ft_lstlast(t_token *lst);

t_redir	*ft_lstredirlast(t_redir *lst);

t_exec	*ft_lstexeclast(t_exec *lst);

t_env	*ft_lstenvlast(t_env *lst);

t_token	*ft_lstnew(char *value, t_tokentype token, t_data *data);

int		ft_lstsize(t_token *lst);

char	**ft_split(char const *s, char c);

int		ft_strlen(const char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strdup(const char *s1);

char	*ft_strdup_env(const char *s1);

char	*ft_strjoin(const char *s1, const char *s2);

void	delete_node(t_token *del, t_data *data);

void	ft_putstr_fd(char *s, int fd);

char	*ft_strtrim(char const *s1, char const *set);

void	delete_node_env(t_env *del, t_data *data);

char	*give_value_env(char *target, t_data *data, int len);

int		ft_isprint(int c);

char	*ft_itoa(int nb);

//  ---- EXEC ----
char	*my_get_path(char *cmd, char **envp);

int		exec_cmd(t_data *data, char **envp);

int		verif_builtin(t_data *data, t_exec *lst);

int		builtin_cd(t_data *data, char *path);

int		builtin_pwd(void);

int		builtin_exit(t_data *data);

int		builtin_env(t_data *data);

int		builtin_unset(t_data *data, char *new_var);

int		builtin_export(t_data *data, char *add_var);

int		builtin_echo(t_data *data, char **args);

//	---- TEST ----
void	test_minishell(t_data *data);

#endif