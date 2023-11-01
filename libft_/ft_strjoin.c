/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:38:08 by omakran           #+#    #+#             */
/*   Updated: 2023/11/01 16:54:31 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	int		i;

	if (!s1 || !s2)
	{
		return (0);
	}
	i = 0;
	arr = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0, ALLOC, 0);
	if (!arr)
		exit (1);
	while (*s1)
	{
		arr[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		arr[i] = *s2;
		s2++;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
