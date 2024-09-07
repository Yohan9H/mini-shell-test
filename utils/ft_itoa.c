/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:08:10 by yohan.h           #+#    #+#             */
/*   Updated: 2024/09/07 15:07:00 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_digit(long n)
{
	int	dgt;

	dgt = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		dgt++;
	}
	return (dgt);
}

static void	ft_cpy(char *str, int digit, int sgn, long n)
{
	int	svg_dgt;

	svg_dgt = digit;
	digit--;
	if (sgn > 0)
	{
		str[0] = '-';
		digit++;
	}
	while ((svg_dgt + sgn) > sgn)
	{
		str[digit] = (n % 10) + '0';
		n /= 10;
		digit--;
		svg_dgt--;
	}
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		digit;
	int		sign;
	long	n;

	n = (long)nb;
	sign = 0;
	if (n < 0)
	{
		sign++;
		n *= -1;
	}
	digit = count_digit(n);
	str = (char *)malloc((digit + sign + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_cpy(str, digit, sign, n);
	str[digit + sign] = '\0';
	return (str);
}

// #include <stdio.h>
// int	main()
// {
// 	char	*str;
// 	int	n = -2147483648;

// 	printf("My function : %s\n", str = ft_itoa(n));
// 	free(str);
// 	return (0);
// }