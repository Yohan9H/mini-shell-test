/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini-shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:29:08 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/14 15:59:08 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# define MALLOC 1 // faire un enum pour les erreurs

typedef enum 
{
	COMMAND_TOKEN,
	STRING_TOKEN,
	PIPE_TOKEN,
	INPUT_TOKEN,
	OUTPUT_TOKEN,
	HEREDOC_TOKEN,
	APPEND_TOKEN,
	REDIRECTION_TOKEN, // au cas ou je dois compter le nb de redirection
} tokentype;

typedef struct s_token t_token;

struct s_token
{
	tokentype	type;
	char		*value;
	t_token		*prev;
	t_token		*next;
};

typedef struct s_lex
{
	char	*input;
	t_token	*first;
	t_token	*last;
	t_token	*new;
	char	*string;
}	t_lex;

typedef struct s_data
{
	t_lex	*lex;
}	t_data;

// ---- MAIN ----
void	exit_clean(t_data *data, int error);

//	---- UTILS ----
void	ft_lstadd_back(t_token **lst, t_token *new, t_token *last);

void	ft_lstadd_front(t_token **lst, t_token *new);

void	ft_lstclear(t_token **lst);

t_token	*ft_lstlast(t_token *lst);

t_token	*ft_lstnew(char *value, tokentype token, t_data *data);

int		ft_lstsize(t_token *lst);

char	**ft_split(char const *s, char c);

int		ft_strlen(const char *s);

// ---- LEXER ----
void	lexer(t_data *data);

int		single_redirection(char *str, t_data *data, int *i);

int		double_redirection(char *str, t_data *data, int *i);

int		check_pipe(char *str, t_data *data, int *i);

int		single_quote(char *str, t_data *data, int *i);

int		double_quote(char *str, t_data *data, int *i);

int		is_string(char *str, t_data *data, int *i);

//	---- UTILS LEXER ----

int		len_db_quote(char *str, int *i, char stop);

int		len_string(char *str, int *i);

void	cpy_str(char *str, t_data *data, int *i, char stop);

#endif