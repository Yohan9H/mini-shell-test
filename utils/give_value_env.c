/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_value_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:42:20 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/19 14:04:29 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_value_env(char *target, t_data *data, int len)
{
	t_env	*lst_env;
	char	*str;

	lst_env = data->my_env;
	while (lst_env != NULL)
	{
		if (ft_strncmp(lst_env->line, target, len) == 0
			&& lst_env->line[len] == '=')
		{
			str = ft_strdup(&lst_env->line[len + 1]);
			return (str);
		}
		lst_env = lst_env->next;
	}
	return (NULL);
}
