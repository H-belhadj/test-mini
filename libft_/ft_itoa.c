/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:13:03 by omakran           #+#    #+#             */
/*   Updated: 2023/11/01 16:53:55 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int nb)
{
	int	counter;

	counter = 0;
	if (nb == 0)
		return (counter + 1);
	if (nb < 0)
	{
		nb = -nb;
		counter++;
	}
	while (nb)
	{
		nb /= 10;
		counter++;
	}
	return (counter);
}

static void	ft_shortcut(int n, char *str)
{
	int		i;
	long	nb;
	int		size;

	size = ft_size(n);
	i = 0;
	nb = n;
	if (nb == 0)
	{
		str[i] = '0';
		str[i + 1] = '\0';
	}
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	str[size] = '\0';
	size--;
	while (nb)
	{
		str[size] = (nb % 10) + 48;
		nb /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;

	str = ft_calloc(1, ft_size(n) * sizeof(char) + 1);
	if (!str)
		exit (1);
	ft_shortcut(n, str);
	return (str);
}
