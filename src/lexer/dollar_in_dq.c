/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_in_dq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:07 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/22 16:06:23 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_in_dq(char *target, t_data *data, int len, int *find)
{
	t_env	*lst_env;
	char	*str;

	*find = -1;
	lst_env = data->my_env;
	while (lst_env != NULL)
	{
		if (ft_strncmp(lst_env->line, target, len) == 0
			&& lst_env->line[len] == '=')
		{
			*find = 1;
			str = ft_strdup(&lst_env->line[len + 1]);
			break ;
		}
		lst_env = lst_env->next;
	}
	if (*find == -1)
		return (NULL);
	else
		return (str);
}

char	*cpy_without_dollar(char *string, t_data *data)
{
	char	*cpy;
	int		i;

	i = 0;
	while (string[i] && i != data->lex->pos_d)
		i++;
	cpy = (char *)malloc((i + 1) * sizeof(char));
	if (!cpy)
		return (exit_clean(data, MALLOC, N_EXIT), NULL);
	i = 0;
	while (string[i] && i != data->lex->pos_d)
	{
		cpy[i] = string[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

void	join_str_value(t_data *data, char *string, char *value_dol, char *aft)
{
	char	*svg;

	svg = cpy_without_dollar(string, data);
	data->lex->string = ft_strjoin(svg, value_dol);
	free(svg);
	free(value_dol);
	value_dol = NULL;
	if (aft != NULL)
	{
		svg = ft_strdup(data->lex->string);
		free(data->lex->string);
		data->lex->string = ft_strjoin(svg, aft);
		free(svg);
		free(aft);
	}
}

void	if_dollar_in_dq(char *string, int len, int pos_d, t_data *data)
{
	char	*value_dol;
	char	*after_dol;
	int		i;

	i = 0;
	pos_d++;
	len = len_string(&string[pos_d], &i, '$');
	value_dol = NULL;
	value_dol = check_if_edge_case(&string[pos_d], data, &i);
	if (value_dol == NULL)
		value_dol = get_value_in_dq(&string[pos_d], data, len, &i);
	after_dol = svg_after_dol(&string[pos_d], &i);
	data->lex->pos_d = pos_d - 1;
	if (i == -1)
		no_find(data, string, after_dol);
	else
		join_str_value(data, string, value_dol, after_dol);
}

void	check_dollar_in_dq(t_data *data, char *string)
{
	int		len;
	int		pos_d;

	pos_d = 0;
	len = 0;
	while (string[0] && string[pos_d])
	{
		if (string[pos_d] && string[pos_d] == '$'
			&& string[pos_d + 1] != ' ' && string[pos_d + 1] != '\0'
			&& string[pos_d + 1] != '\'')
		{
			if_dollar_in_dq(string, len, pos_d, data);
			free(string);
			string = data->lex->string;
			pos_d = 0;
		}
		pos_d++;
	}
}
