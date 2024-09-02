/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_in_dq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:07 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/29 11:54:39 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_in_dq(char *target, t_data *data, int len, int *find)
{
	char	*str;
	int	j;

	j = 0;
	*find = -1;
	while (data->my_env[j])
	{
		if (ft_strncmp(data->my_env[j], target, len) == 0
			&& data->my_env[j][len] == '=')
		{
			*find = 1;
			str = ft_strdup(&(data->my_env)[j][len + 1]);
			break;
		}
		j++;
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
	while (string[i] && string[i] != '$')
		i++;
	cpy = (char *)malloc((i + 1) * sizeof(char));
	if (!cpy)
		return (exit_clean(data, MALLOC, N_EXIT), NULL);
	i = 0;
	while (string[i] && string[i] != '$')
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

void	if_dollar_in_dq(char *string, int len, int pos_D, t_data *data)
{
	char	*value_dol;
	char	*after_dol;
	char	*svg;
	int		i;

	i = 0;
	pos_D++;
	len = len_string(&string[pos_D], &i);
	value_dol = get_value_in_dq(&string[pos_D], data, len, &i);
	after_dol = svg_after_dol(&string[pos_D]);
	if (i == -1)
	{
		data->lex->string = cpy_without_dollar(string, data);
		if (after_dol != NULL)
		{
			svg = ft_strdup(data->lex->string);
			free(data->lex->string);
			data->lex->string = ft_strjoin(svg, after_dol);
			free(svg);
			free(after_dol);
		}
	}
	else
		join_str_value(data, string, value_dol, after_dol);
}

void	check_dollar_in_dq(t_data *data, char *string)
{
	int		len;
	int		pos_D;

	pos_D = 0;
	len = 0;
	while (string[0] && string[pos_D])
	{
		if (string[pos_D] && string[pos_D] == '$')
		{
			if_dollar_in_dq(string, len, pos_D, data);
			free(string);
			string = data->lex->string;
			pos_D = 0;
		}
		pos_D++;
	}
}
