/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:12:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/25 17:30:52 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**my_env_to_tab(t_env *env)
{
	t_env	*lst;
	char	**tab;
	size_t	size;
	int		i;

	lst = env;
	size = ft_lstsize_env(env);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst)
	{
		tab[i] = ft_strdup(lst->line);
		if (!tab[i])
		{
			freetab(tab);
			return (NULL);
		}
		i++;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*my_get_env(t_data *data, char *name)
{
	int		j;
	char	*sub;
	t_env	*lst;

	lst = data->my_env;
	while (lst)
	{
		j = 0;
		while (lst->line[j] && lst->line[j] != '=')
			j++;
		sub = ft_substr(lst->line, 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (lst->line + j + 1);
		}
		free(sub);
		lst = lst->next;
	}
	return (NULL);
}

char	*my_get_exec(char *cmd, char **total_path)
{
	int		i;
	char	*path;
	char	*exec;

	i = 0;
	while (total_path[i])
	{
		path = ft_strjoin(total_path[i], "/");
		if (!path)
			return (NULL);
		exec = ft_strjoin(path, cmd);
		free(path);
		if (!exec)
			return (NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
		i++;
	}
	return (NULL);
}

// int	is_absolute_path(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '/')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

char	*my_get_path(char *cmd, t_data *data)
{
	char	*exec;
	char	**total_path;

	if (cmd && cmd[0] == '\0')
		return (NULL);
	if (!data->my_env || (access(cmd, F_OK | X_OK) == 0))
		return (ft_strdup(cmd));
	total_path = ft_split(my_get_env(data, "PATH"), ':');
	if (!total_path)
		return (ft_strdup(cmd));
	exec = my_get_exec(cmd, total_path);
	freetab(total_path);
	return (exec);
}
