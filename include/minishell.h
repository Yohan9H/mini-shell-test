/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:30:42 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/21 10:59:49 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "lexer.h"
# include "parser.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum
{
	MALLOC,
	QUOTE_CLOSE,
	NOTHING,
} type_error;

typedef struct s_data
{
	t_lex	*lex;
	int		code_reset;
}	t_data;

//	---- MAIN ----
void	print_error(int error);

void	exit_clean(t_data *data, type_error error, bool num);

//	---- UTILS ----
void	ft_lstadd_back(t_token **lst, t_token *new, t_token *last);

void	ft_lstadd_front(t_token **lst, t_token *new);

void	ft_lstclear(t_token **lst);

t_token	*ft_lstlast(t_token *lst);

t_token	*ft_lstnew(char *value, tokentype token, t_data *data);

int		ft_lstsize(t_token *lst);

char	**ft_split(char const *s, char c);

int		ft_strlen(const char *s);

//	---- TEST ----
void	test_minishell(t_data *data);

#endif