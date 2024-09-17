/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:37:52 by yohurteb          #+#    #+#             */
/*   Updated: 2024/09/17 17:33:53 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_putchar_error(char c)
{
	write(1, &c, 1);
	return (1);
}

int	nb_base_long(unsigned long nb, char *base, unsigned long size_b)
{
	int	i;

	i = 0;
	if (nb >= size_b)
	{
		i += nb_base_long(nb / size_b, base, size_b);
	}
	ft_putchar_error(base[nb % size_b]);
	i++;
	return (i);
}

int	verif_nil(unsigned long nb, char *base, unsigned long size_b)
{
	if (nb != 0)
	{
		write(1, "0x", 2);
		return (nb_base_long(nb, base, size_b) + 2);
	}
	else
	{
		write(1, "(nil)", 5);
		return (5);
	}
}
