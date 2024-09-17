/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:02:11 by yohan.h           #+#    #+#             */
/*   Updated: 2024/09/17 14:25:41 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_signe(const char *str, size_t *i)
{
	int		sgn;

	sgn = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sgn = -1;
		*i = *i + 1;
	}
	return (sgn);
}

int	ft_atoi(const char *str)
{
	size_t			i;
	int				signe;
	unsigned char	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	signe = verif_signe(str, &i);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * signe);
}

/*#include <stdlib.h>
#include <stdio.h>
int main()
{
	const char	str[] = "   \t 123abc4";

	printf("My function   : %d\n", ft_atoi(str));
	printf("Reel function : %d\n", atoi(str));
	return (0);
}*/