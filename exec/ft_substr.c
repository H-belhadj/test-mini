/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:24:37 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 16:31:25 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	n;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	arr = ft_calloc(len + 1, sizeof(char));
	if (!arr)
		return (NULL);
	n = 0;
	while (n < len && s[start + n])
	{
		arr[n] = s[start + n];
		n++;
	}
	return (arr);
}
