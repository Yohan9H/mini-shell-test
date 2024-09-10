/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:51:04 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/10 14:04:34 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(t_tokentype type)
{
	if (type == SPACE_TK)
		return ("SPACE_TK");
	if (type == DOLLAR_TOKEN)
		return ("DOLLAR_TOKEN");
	if (type == DOLLAR_FAIL)
		return ("DOLLAR_FAIL");
	if (type == FILE_TOKEN)
		return ("FILE_TOKEN");
	if (type == STRING_TOKEN)
		return ("STRING_TOKEN");
	if (type == PIPE_TK)
		return ("PIPE_TK");
	if (type == INPUT_TK)
		return ("INPUT_TK");
	if (type == OUTPUT_TK)
		return ("OUTPUT_TK");
	if (type == HEREDOC_TK)
		return ("HEREDOC_TK");
	if (type == APPEND_TK)
		return ("APPEND_TK");
	if (type == DQ_TOKEN)
		return ("DQ_TOKEN");
	if (type == SQ_TOKEN)
		return ("SQ_TOKEN");
	return (NULL);
}

void	test_minishell(t_data *data)
{
	t_token	*tmp = NULL;
	t_exec	*tmp_exec = NULL;
	t_redir	*tmp_redir = NULL;
	t_env	*tmp_env = NULL;
	int	j;
	int	i;

	i = 0;
	tmp = data->lex->first;
	tmp_exec = data->head;
	tmp_env = data->my_env;
	// -------------   ENV   --------------
	// while (tmp_env != NULL)
	// {
	// 	printf("%s\n", tmp_env->line);
	// 	tmp_env = tmp_env->next;
	// }
	// -------------   LEXER   --------------
	printf("  ----  \n");
	while (tmp != NULL)
	{
		printf("num : %d\n", i++);
		printf("value type : %s\n", get_token(tmp->type));
		printf("value node : %s\n  ----  \n", tmp->value);
		tmp = tmp->next;
	}
	// -------------   PARSER   --------------
	printf("\n////////////////\n");
	while (tmp_exec != NULL)
	{
		printf("cmd = %s\n", tmp_exec->cmd);
		printf("args /\n");
		j = 0;
		while (tmp_exec->args[j])
		{
			printf("  -> %s\n", tmp_exec->args[j]);
			j++;
		}
		printf("redirection /\n");
		tmp_redir = tmp_exec->redir;
		while (tmp_redir != NULL)
		{
			printf("     filename -> %s\n", tmp_redir->filename);
			printf("     type     -> %s\n", get_token(tmp_redir->type));
			tmp_redir = tmp_redir->next;
		}
		printf("\n////////////////\n");
		tmp_exec = tmp_exec->next;
	}
}
