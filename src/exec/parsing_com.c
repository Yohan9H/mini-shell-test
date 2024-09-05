/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apernot <apernot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:12:11 by apernot           #+#    #+#             */
/*   Updated: 2024/09/04 16:30:08 by apernot          ###   ########.fr       */
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

char	*my_get_env(char **envp, char *name)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*my_get_path(char *cmd, char **envp)
{
	int		i;
	char	**com;
	char	*path;
	char	*exec;
	char	**total_path;

	i = 0;
	total_path = ft_split(my_get_env(envp, "PATH"), ':');
	com = ft_split(cmd, ' ');
	while (total_path[i])
	{
		path = ft_strjoin(total_path[i], "/");
		exec = ft_strjoin(path, com[0]);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			freetab(com);
			return (exec);
		}
		free(exec);
		i++;
	}
	freetab(total_path);
	freetab(com);
	return (cmd);
}
