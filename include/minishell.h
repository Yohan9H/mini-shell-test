/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:30:42 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/20 14:22:04 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "lexer.h"
# include "parser.h"
# include "env.h"
# include "exec.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h> 
# include <linux/limits.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int	g_var_global;

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
	unsigned char exit_code;
}	t_data;

//	---- MAIN ----
void	init_data(t_data *data, char **env);

void	print_error(int error, t_data *data);

void	exit_clean(t_data *data, t_type_error error, t_bool num);

//  ---- SIGNALS ---- 
void	init_sig(void);

//	---- UTILS ----
void	ft_lstadd_back(t_token **lst, t_token *new, t_token **last);

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

int		ft_lstsize_env(t_env *env);

char	**ft_split(char const *s, char c);

int		ft_strlen(const char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strdup(const char *s1);

char	*ft_strdup_env(const char *s1);

char	*ft_strjoin(const char *s1, const char *s2);

void	delete_node(t_token *del, t_data *data);

void	ft_putstr_fd(char *s, int fd);

void	delete_node_env(t_env *del, t_data *data);

char	*give_value_env(char *target, t_data *data, int len);

int		ft_isprint(int c);

char	*ft_itoa(int nb);

int		ft_atoi(const char *str);

int		ft_fprintf(const char *format, ...);

int		verif_nil(unsigned long nb, char *base, unsigned long size_b);

//  ---- EXEC ----
char	*my_get_path(char *cmd, t_data *data);

int		exec_cmd(t_data *data);

int		verif_builtin(t_data *data, t_exec *lst, t_execom *execom);

int		builtin_cd(t_data *data, char **args);

int		builtin_pwd(t_data *data);

int		builtin_exit(t_data *data, char **args, t_execom *execom);

int		builtin_env(t_data *data, char **args);

int		builtin_unset(t_data *data, char **delete_var);

void	delete_if_exist(t_data *data, char *name);

int		builtin_export(t_data *data, char **new);

int		builtin_echo(t_data *data, char **args);

char	**my_env_to_tab(t_env *env);

void	handle_sigint_heredoc(int sig);

//	---- TEST ----
void	test_minishell(t_data *data);

#endif