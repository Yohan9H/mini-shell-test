/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:54:53 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/23 10:51:08 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

// ---- PARSER ----
void	parser(t_data *data);

void	state_pipe(t_data *data, t_token *lst);

void	state_redirection(t_data *data, t_token *lst);

// ---- VERIF STATE ----
void	verif_nothing(t_data *data, t_token *lst);

void	verif_same_tk(t_data *data, t_token *lst, tokentype type);

void	verif_redirection_pipe(t_data *data, t_token *lst);

// ---- UTILS PARSER ----
int		is_redirection(tokentype type);

#endif