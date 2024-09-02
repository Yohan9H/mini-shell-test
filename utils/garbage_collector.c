/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:56:23 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/02 14:19:22 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error)
{
	if (error == MALLOC)
		fprintf(stderr, "error : malloc\n");
	if (error == QUOTE_CLOSE)
		fprintf(stderr, "error : quote not close\n");
}

void	clean_my_env(t_data *data)
{
	if (data->my_env)
	{
		ft_lstclear_env(&data->my_env);
		data->my_env = NULL;
	}
}

void	if_exit(t_data *data, bool num)
{
	if (num == Y_EXIT)
	{
		if (data->lex)
		{
			free(data->lex);
			data->lex = NULL;
		}
		if (data->par)
		{
			free(data->par);
			data->par = NULL;
		}
		clean_my_env(data);
		exit(1);
	}
	else if (num == N_EXIT)
		data->code_reset = 1;
	else
		return ;
}

void	clean_data_parser(t_data *data)
{
	if (data->par->first)
	{
		ft_lstclear_exec(&(data->par->first));
		data->par->first = NULL;
	}
	if (data->par->new)
	{
		free(data->par->new);
		data->par->new = NULL;
	}
	if (data->par->new_redir)
	{
		free(data->par->new_redir);
		data->par->new_redir = NULL;
	}
}

void	exit_clean(t_data *data, type_error error, bool num)
{
	if (data->lex->first)
	{
		ft_lstclear(&(data->lex->first));
		data->lex->first = NULL;
	}
	if (data->lex->input)
	{
		free(data->lex->input);
		data->lex->input = NULL;
	}
	if (data->lex->new)
	{
		free(data->lex->new);
		data->lex->new = NULL;
	}
	clean_data_parser(data);
	print_error(error);
	if_exit(data, num);

}
