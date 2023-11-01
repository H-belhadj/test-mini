/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:29:38 by omakran           #+#    #+#             */
/*   Updated: 2023/11/01 16:54:31 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	n;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	n = 0;
	arr = ft_malloc(len + 1 * sizeof(char), 0, ALLOC, 0);
	if (!arr)
		exit (1);
	while (n < len && start < ft_strlen(s))
	{
		arr[n] = s[start];
		n++;
		start++;
	}
	arr[n] = '\0';
	return (arr);
}
