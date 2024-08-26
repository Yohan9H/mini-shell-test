/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:51:04 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/26 13:29:55 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(tokentype type)
{
	if (type == SPACE_TK)
		return ("SPACE_TK");
	if (type == DOLLAR_TOKEN)
		return ("DOLLAR_TOKEN");
	if (type == FILE_TOKEN)
		return ("FILE_TOKEN");
	if (type == STRING_TOKEN)
		return ("STRING_TOKEN");
	if (type == PIPE_TOKEN)
		return ("PIPE_TOKEN");
	if (type == INPUT_TOKEN)
		return ("INPUT_TOKEN");
	if (type == OUTPUT_TOKEN)
		return ("OUTPUT_TOKEN");
	if (type == HEREDOC_TOKEN)
		return ("HEREDOC_TOKEN");
	if (type == APPEND_TOKEN)
		return ("APPEND_TOKEN");
	if (type == DQ_TOKEN)
		return ("DQ_TOKEN");
	if (type == SQ_TOKEN)
		return ("SQ_TOKEN");
	return (NULL);
}

void	test_minishell(t_data *data)
{
	t_token	*tmp = NULL;
	int	i;

	i = 0;
	tmp = data->lex->first;
	printf("  ----  \n");
	while (tmp != NULL)
	{
		if (tmp->type != SPACE_TK)
		{
			printf("num : %d\n", i++);
			printf("value type : %s\n", get_token(tmp->type));
			printf("value node : %s\n  ----  \n", tmp->value);
		}
		tmp = tmp->next;
	}
}
