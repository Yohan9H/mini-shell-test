/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:54:53 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/20 14:54:21 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef	enum
{
	W_INPUT,
	W_OUTPUT,
	W_PIPE,
}	error_pars;

// ---- PARSER ----
void	parser(t_data *data);

void	prep_parser(t_data *data);

// ---- PARSER ----
int		is_str_sg_db(tokentype type);

int		is_redirection(tokentype type);

#endif