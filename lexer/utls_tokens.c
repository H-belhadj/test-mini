/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakran <omakran@student.1337.ma >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:10:44 by omakran           #+#    #+#             */
/*   Updated: 2023/10/27 11:14:48 by omakran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_odd(int nbr)
{
	if (nbr % 2 == 0)
		return (1);
	return (0);
}

char	*get_elemnts(int start, int length, char *str)
{
	int		i;
	char	*dst;

	i = 0;
	dst = ft_malloc(sizeof(char) * (length + 1), 0, ALLOC, 0);
	if (!dst)
		exit(1);
	while (str[start] && (i < length))
	{
		dst[i] = str[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*split_redirections(int start, char *str)
{
	int		i;
	int		length;
	int		starttwo;
	char	*dst;

	starttwo = start;
	length = 0;
	i = 0;
	while (str[starttwo] && (str[starttwo] == '>' || str[starttwo] == '<'))
	{
		length++;
		starttwo++;
	}
	dst = ft_malloc(sizeof(char) * (length + 1), 0, ALLOC, 0);
	if (!dst)
		exit(1);
	while (str[start] && (str[start] == '>' || str[start] == '<'))
	{
		dst[i] = str[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

int	is_only_space_and_tab(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
