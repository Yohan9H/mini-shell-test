/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:12:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/11 13:32:13 by apernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (start + len > len_s)
		len = len_s - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	freetab(char **com)
{
	int	i;

	i = 0;
	while (com[i])
	{
		free(com[i]);
		i++;
	}
	free(com);
}
char	**my_env_to_tab(t_env *env)
{
	t_env *lst;
	char **tab;
	size_t	size;
	int i;

	lst = env;
	size = ft_lstsize_env(env);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst)
	{
		tab[i] = (char *)malloc(sizeof(char) * (ft_strlen(lst->line) + 1));
		if (!tab[i])
			return (NULL);
		tab[i] = ft_strdup(lst->line);
		i++;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*my_get_env(t_data *data, char *name)
{
	int	j;
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

// char	*my_get_path(char *cmd, t_data *data)
// {
// 	int		i;
// 	char	**com;
// 	char	*path;
// 	char	*exec;
// 	char	**total_path;

// 	i = 0;
// 	total_path = ft_split(my_get_env(data, "PATH"), ':');
// 	com = ft_split(cmd, ' ');
// 	while (total_path[i])
// 	{
// 		path = ft_strjoin(total_path[i], "/");
// 		exec = ft_strjoin(path, com[0]);
// 		free(path);
// 		if (access(exec, F_OK | X_OK) == 0)
// 		{
// 			freetab(com);
// 			return (exec);
// 		}
// 		free(exec);
// 		i++;
// 	}
// 	freetab(total_path);
// 	freetab(com);
// 	return (cmd);
// }


char	*my_get_exec(char *cmd, char **total_path)
{
	int i;
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

char	*my_get_path(char *cmd, t_data *data)
{
	int		i;
	char	**com;
	char	*path;
	char	*exec;
	char	**total_path;

	i = 0;
	if (cmd && cmd[0] == '\0')
		return (NULL);
	if (!data->my_env || is_absolute_path(cmd) == 1) // rajouter condition si chemin absolu
		return (ft_strdup(cmd));
	total_path = ft_split(my_get_env(data, "PATH"), ':');
	if (!total_path)
		return (ft_strdup(cmd));
	exec = my_get_exec(cmd, total_path);
	freetab(total_path);
	return (exec);
}

int	is_absolute_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
