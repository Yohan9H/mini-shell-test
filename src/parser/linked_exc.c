/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_exc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:12:17 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/23 13:03:59 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_nb_args(t_token *l_lex)
{
	t_token	*lst;
	int		nb_str;

	lst = l_lex;
	nb_str = 0;
	while (lst != NULL && lst->type != PIPE_TK)
	{
		if (lst->type == STRING_TOKEN)
			nb_str++;
		lst = lst->next;
	}
	return (nb_str);
}

char	**cpy_args(t_token *l_lex, t_data *data)
{
	t_token	*lst;
	char	**new;
	int		nb_args;
	int		i;

	nb_args = calculate_nb_args(l_lex);
	lst = l_lex;
	i = 0;
	new = (char **)malloc((nb_args + 1) * sizeof(char *));
	while (lst != NULL && lst->type != PIPE_TK)
	{
		if (lst->type == STRING_TOKEN)
		{
			new[i] = ft_strdup(lst->value);
			if (!new[i])
				exit_clean(data, MALLOC, N_EXIT);
			i++;
		}
		lst = lst->next;
	}
	new[i] = NULL;
	return (new);
}

t_exec	*ft_lstnew_node(t_data *data, t_token *l_lex)
{
	t_token	*svg;
	t_token	*find_cmd;
	t_exec	*new;

	new = (t_exec *)malloc(sizeof(t_exec));
	svg = l_lex;
	if (svg != NULL && svg->type != STRING_TOKEN)
	{
		find_cmd = svg;
		while (find_cmd != NULL && (find_cmd->type \
			!= STRING_TOKEN || is_redirection(find_cmd->type) == 0))
			find_cmd = find_cmd->next;
		if (find_cmd != NULL)
			new->cmd = ft_strdup(find_cmd->value);
		else
			new->cmd = NULL;
	}
	else
		new->cmd = ft_strdup(svg->value);
	new->args = cpy_args(svg, data);
	new->redir = create_linked_lst_redir(data, svg);
	new->next = NULL;
	return (new);
}

void	create_linked_lst_exec(t_data *data)
{
	t_token	*l_lex;

	l_lex = data->lex->first;
	while (l_lex != NULL)
	{
		if (l_lex != NULL && l_lex->type == PIPE_TK)
			l_lex = l_lex->next;
		data->par->new = ft_lstnew_node(data, l_lex);
		ft_execadd_back(&data->par->first, data->par->new);
		data->par->new = NULL;
		while (l_lex != NULL && l_lex->type != PIPE_TK)
			l_lex = l_lex->next;
	}
}
