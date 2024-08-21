/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:32:47 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/21 14:33:03 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_sg_db(tokentype type)
{
	if (type == STRING_TOKEN || type == DB_TOKEN || type == SG_TOKEN)
		return (1);
	else
		return (0);
}

int	is_redirection(tokentype type)
{
	if (type == INPUT_TOKEN || type == OUTPUT_TOKEN || type == APPEND_TOKEN 
		|| type == HEREDOC_TOKEN)
		return (1);
	else
		return (0);
}
