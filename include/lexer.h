/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:29:08 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/09 17:57:33 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# define STRING ' '
# define DOUBLE_Q '"'
# define SINGLE_Q '\''

typedef struct s_data	t_data;

typedef enum e_bool
{
	Y_EXIT,
	N_EXIT,
}	t_bool;

typedef enum e_tokentype
{
	SPACE_TK,
	FILE_TOKEN,
	DOLLAR_TOKEN,
	DOLLAR_FAIL,
	STRING_TOKEN,
	DQ_TOKEN,
	SQ_TOKEN,
	PIPE_TK,
	INPUT_TK,
	OUTPUT_TK,
	HEREDOC_TK,
	APPEND_TK,
}	t_tokentype;

typedef struct s_token	t_token;

struct s_token
{
	t_tokentype	type;
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

// ---- LEXER ----
void	lexer(t_data *data);

int		check_space(char *str, t_data *data, int *i);

int		single_redirection(char *str, t_data *data, int *i);

int		double_redirection(char *str, t_data *data, int *i);

int		check_pipe(char *str, t_data *data, int *i);

int		single_quote(char *str, t_data *data, int *i);

int		double_quote(char *str, t_data *data, int *i);

char	*svg_after_dol(char *string);

void	check_dollar_in_dq(t_data *data, char *string);

int		is_string(char *str, t_data *data, int *i);

int		is_dollar(char *str, t_data *data, int *i);

int		get_value(char *target, t_data *data, int len);

void	add_file_tk(t_token *first);

void	join_if_no_space_and_del_space(t_data *data);

int		is_str_sq_dq_dol(t_tokentype type);

//	---- UTILS LEXER ----
int		len_db_quote(char *str, int *i, char stop);

int		len_string(char *str, int *i, char code);

void	cpy_str(char *str, t_data *data, int *i, char stop);

int		verif_sep_close(char *str, int *i, char type, int len);

int		is_allspace(char c);

int		is_metachar(char c);

#endif