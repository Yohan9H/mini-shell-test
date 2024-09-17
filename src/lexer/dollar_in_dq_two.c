/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_in_dq_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:37:37 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/17 10:01:57 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*svg_after_dol(char *string, int *if_code)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = NULL;
	if (*if_code == 2)
	{
		cpy = ft_strdup(&string[1]);
		return (cpy);
	}
	while (string[i] && is_allspace(string[i]) != 1 && string[i] != '\''
		&& string[i] != '$')
		i++;
	if (string[i])
		cpy = ft_strdup(&string[i]);
	return (cpy);
}

char	*check_if_code(char *str, t_data *data, int *status)
{
	char	*str_code;

	str_code = NULL;
	if (str[0] == '?')
	{
		*status = 2;
		str_code = ft_itoa(data->exit_code);
	}
	return (str_code);
}
