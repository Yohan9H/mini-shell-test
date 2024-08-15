/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:43:49 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/15 14:37:56 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini-shell.h"

// plus tard gerer les autres separateurs telle que le retour a la ligne et le tab
int	is_string(char *str, t_data *data, int *i)
{
	int len;

	if (str[*i] != ' ')
	{
		len = len_string(str, i);
		data->lex->string = malloc((len + 1) * sizeof(char));
		if (!data->lex->string)
			exit_clean(data, MALLOC);
		cpy_str(str, data, i, ' ');
		data->lex->new = ft_lstnew(data->lex->string, STRING_TOKEN, data);
		return (1);
	}
	return (0);
}
