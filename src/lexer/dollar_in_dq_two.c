/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_in_dq_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:37:37 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/08 13:49:53 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*svg_after_dol(char *string)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = NULL;
	while (string[i] && is_allspace(string[i]) != 1 && string[i] != '\''
		&& string[i] != '$')
		i++;
	if (string[i])
		cpy = ft_strdup(&string[i]);
	return (cpy);
}
