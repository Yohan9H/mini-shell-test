/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:32:43 by yohurteb          #+#    #+#             */
/*   Updated: 2024/08/31 11:44:48 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if (is_str_sq_dq_dol((*lst)->type) == 1
		|| (*lst)->type == DOLLAR_FAIL || (*lst)->type == FILE_TOKEN)
			free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstclear_redir(t_redir **lst)
{
	t_redir	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->filename)
		{
			free((*lst)->filename);
			(*lst)->filename = NULL;
		}
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstclear_exec(t_exec **lst)
{
	t_exec	*tmp;
	int		i;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->cmd);
		i = 0;
		while ((*lst)->args[i])
		{
			free((*lst)->args[i]);
			(*lst)->args[i] = NULL;
			i++;
		}
		if ((*lst)->args)
		{
			free((*lst)->args);
			(*lst)->args = NULL;
		}
		ft_lstclear_redir(&(*lst)->redir);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
