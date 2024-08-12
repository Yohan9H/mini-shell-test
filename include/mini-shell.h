/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini-shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:29:08 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/12 14:09:55 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum 
{
	COMMAND_TOKEN,
	STRING_TOKEN,
	PIPE_TOKEN,
	REDIRECTION_TOKEN,
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
}	t_lex;

typedef struct s_data
{
	t_lex	*lex;
}	t_data;

char	*lexer(t_data *data);

void	ft_lstadd_back(t_token **lst, t_token *new);

void	ft_lstadd_front(t_token **lst, t_token *new);

void	ft_lstclear(t_token **lst);

t_token	*ft_lstlast(t_token *lst);

t_token	*ft_lstnew(char *value, tokentype token);

int		ft_lstsize(t_token *lst);

char	**ft_split(char const *s, char c);

#endif