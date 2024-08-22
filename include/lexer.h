/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:29:08 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/22 15:21:38 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# define STRING ' '
# define DOUBLE_Q '"'
# define SINGLE_Q '\''

typedef struct s_data	t_data;

typedef enum
{
	Y_EXIT,
	N_EXIT,
} bool;

typedef enum
{
	FILE_TOKEN,
	DOLLAR_TOKEN,
	STRING_TOKEN,
	DQ_TOKEN,
	SQ_TOKEN,
	PIPE_TOKEN,
	INPUT_TOKEN,
	OUTPUT_TOKEN,
	HEREDOC_TOKEN,
	APPEND_TOKEN,
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

// ---- LEXER ----
void	lexer(t_data *data);

int		single_redirection(char *str, t_data *data, int *i);

int		double_redirection(char *str, t_data *data, int *i);

int		check_pipe(char *str, t_data *data, int *i);

int		single_quote(char *str, t_data *data, int *i);

int		double_quote(char *str, t_data *data, int *i);

int		is_string(char *str, t_data *data, int *i);

int		is_dollar(char *str, t_data *data, int *i);

void	add_file_tk(t_token *first);


//	---- UTILS LEXER ----
int		len_db_quote(char *str, int *i, char stop);

int		len_string(char *str, int *i);

void	cpy_str(char *str, t_data *data, int *i, char stop);

int		verif_sep_close(char *str, int *i, char type, int len);

#endif