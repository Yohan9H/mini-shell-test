/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:43:18 by yohan.h           #+#    #+#             */
/*   Updated: 2024/08/15 14:58:01 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	if (i == 0)
		return (0);
	else
		return (count);
}

static int	len_split(char const *s, char c, size_t *i, size_t *skip_c)
{
	int	return_value;

	return_value = 0;
	if (*i > 0)
		*i = *i + 1;
	while (s[*skip_c] == c && s[*skip_c])
		*skip_c = *skip_c + 1;
	while (s[*skip_c] != c && s[*skip_c])
	{
		*i = *i + 1;
		*skip_c = *skip_c + 1;
		return_value++;
	}
	*i = *skip_c;
	return (return_value);
}

static void	split_cpy(char const *s, char *str, char c, size_t *o)
{
	size_t	i;

	i = 0;
	while (s[*o] == c && s[*o])
		*o = *o + 1;
	while (s[*o] != c && s[*o])
	{
		str[i] = s[*o];
		*o = *o + 1;
		i++;
	}
	if (s[*o])
		*o = *o + 1;
	str[i] = '\0';
}

static int	split_dup(char const *s, char **str, char c, size_t *ct_word)
{
	int		k;
	size_t	svg;
	size_t	o;
	size_t	skp;

	skp = 0;
	k = 0;
	svg = 0;
	o = 0;
	while (k < (int)*ct_word)
	{
		str[k] = (char *)malloc(len_split(s, c, &svg, &skp) + 1 * sizeof(char));
		if (!str[k])
		{
			while (k >= 0)
				free(str[k--]);
			free(str);
			return (1);
		}
		split_cpy(s, str[k], c, &o);
		k++;
	}
	str[k] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	ct_word;

	ct_word = ft_count_words(s, c);
	str = (char **)malloc((ct_word + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (split_dup(s, str, c, &ct_word) == 1)
		return (NULL);
	return (str);
}

// #include <stdio.h>
// int	main()
// {
// 	char const	*s = "^^^1^^2a,^^^^3^^^^--h^^^^";
// 	char		c = '^';
// 	char		**str;
// 	size_t		i = 0;

// 	str = ft_split(s, c);
// 	printf("My function :\n");
// 	while (str[i])
// 	{
// 		printf("%s\n", str[i]);
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }
