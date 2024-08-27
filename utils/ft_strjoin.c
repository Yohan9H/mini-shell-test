/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:13:44 by yohan.h           #+#    #+#             */
/*   Updated: 2024/08/27 15:09:16 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len_total;
	size_t	i;

	i = 0;
	len_total = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len_total * sizeof(char));
	if (!str)
		return (NULL);
	len_total = 0;
	while (s1[i])
	{
		str[len_total] = s1[i];
		len_total++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[len_total] = s2[i];
		len_total++;
		i++;
	}
	str[len_total] = '\0';
	return (str);
}

/*#include <stdio.h>
int	main()
{
	const char	s1[] = "";
	const char	s2[] = "";
	char		*str;

	printf("My function : %s\n", str = ft_strjoin(s1, s2));
	free(str);
}*/