/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_exc_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:58:00 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/20 16:48:51 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_name(int counter)
{
	char	*name;
	char	*str_counter;
	char	*base;

	str_counter = NULL;
	base = ft_strdup(".heredoc");
	name = ft_strdup(".heredoc");
	while (1)
	{
		if (access(name, F_OK) == -1)
		{
			if (str_counter != NULL)
				free(str_counter);
			free(base);
			return (name);
		}
		counter++;
		if (str_counter != NULL)
			free(str_counter);
		str_counter = ft_itoa(counter);
		free(name);
		name = ft_strjoin(base, str_counter);
	}
	return (name);
}

void	put_value_in_heredoc(char *eof, int fd, t_data *data)
{
	char	*line;
	char	*tmp;

	signal(SIGINT, handle_sigint_heredoc);
	rl_event_hook = event_hook;
	while (1)
	{
		line = readline("> ");
		if (check_if_break(data, line, eof, fd) == 1)
			break ;
		tmp = ft_strjoin(line, "\n");
		ft_putstr_fd(tmp, fd);
		free(line);
		free(tmp);
	}
	rl_event_hook = NULL;
	init_sig();
}

void	create_heredoc(t_data *data, t_redir *new, char *eof)
{
	int		fd;
	int		counter_for_name;

	counter_for_name = 0;
	new->filename = find_name(counter_for_name);
	fd = open(new->filename, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
		exit_clean(data, OPEN, Y_EXIT);
	if (data->code_reset == 0)
		put_value_in_heredoc(eof, fd, data);
	close(fd);
	unlink(new->filename);
	new->type = HEREDOC_TK;
	new->next = NULL;
}

t_redir	*new_node_redir(t_data *data, t_token *lst, t_tokentype type)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		exit_clean(data, MALLOC, Y_EXIT);
	if (type == HEREDOC_TK)
	{
		create_heredoc(data, new, lst->next->value);
		return (new);
	}
	new->filename = ft_strdup(lst->next->value);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_redir	*create_linked_lst_redir(t_data *data, t_token *l_lex)
{
	t_token	*lst;
	t_redir	*new_linked_rdr;

	lst = l_lex;
	new_linked_rdr = NULL;
	while (lst != NULL && lst->type != PIPE_TK)
	{
		if (is_redirection(lst->type) == 1)
		{
			data->par->new_redir = new_node_redir(data, lst, lst->type);
			ft_rediradd_back(&new_linked_rdr, data->par->new_redir);
			data->par->new_redir = NULL;
		}
		lst = lst->next;
	}
	data->par->new_redir = NULL;
	return (new_linked_rdr);
}
