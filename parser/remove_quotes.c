/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:55:08 by omakran           #+#    #+#             */
/*   Updated: 2023/11/03 19:23:25 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_new_str(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			ret++;
		i++;
	}
	return (ret);
}

char	*rm_quote(char *str)
{
	int		i;
	int		counter;
	char	*new_str;

	new_str = ft_malloc(sizeof(char) * (count_new_str(str) + 1), 0, ALLOC, 0);
	if (!new_str)
		exit(1);
	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			new_str[counter] = str[i];
			counter++;
		}
		i++;
	}
	new_str[counter] = '\0';
	return (new_str);
}

char	**remove_quotes(char **tokens)
{
	int		i;
	char	*token;

	i = 0;
	while (tokens[i])
	{
		token = tokens[i];
		tokens[i] = rm_quote(token);
		i++;
	}
	tokens[i] = NULL;
	if (!tokens[0])
	{
		tokens = malloc(sizeof(char *) * (1));
		tokens[0] = "";
	}
	return (tokens);
}
