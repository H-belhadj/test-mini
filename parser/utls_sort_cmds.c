/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_sort_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakran <omakran@student.1337.ma >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:22:52 by omakran           #+#    #+#             */
/*   Updated: 2023/10/27 11:24:28 by omakran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(char **tokens)
{
	int	i;
	int	count_cmds;

	i = 0;
	count_cmds = 0;
	while (tokens[i])
	{
		if (tokens[i + 1] && (ft_strncmp(tokens[i + 1], "|", ft_strlen(tokens[i \
						+ 1])) == 0))
			count_cmds++;
		else if (!tokens[i + 1])
			count_cmds++;
		i++;
	}
	return (count_cmds);
}

int	is_redirection(char *str)
{
	if (str_cmp(str, ">") || str_cmp(str, ">>") || str_cmp(str, "<<")
		|| str_cmp(str, "<"))
		return (1);
	return (0);
}

char	**fill_commads(char **dst, char **tokens, int start, int end)
{
	int	i;

	i = 0;
	while (tokens[start] && start < end)
	{
		if (start == 0 || ((start - 1 >= 0 && !is_redirection(tokens[start \
						- 1])) && !is_redirection(tokens[start])))
		{
			if (start == 0 && !is_redirection(tokens[start]))
			{
				dst[i] = tokens[start];
				i++;
			}
			else if ((start - 1 >= 0 && !is_redirection(tokens[start - 1]))
				&& !is_redirection(tokens[start]))
			{
				dst[i] = tokens[start];
				i++;
			}
		}
		start++;
	}
	dst[i] = NULL;
	return (dst);
}

int	count_opertors_and_file(char **tokens, int start, int end)
{
	int	i;

	i = 0;
	while (tokens[start] && start < end)
	{
		if (is_redirection(tokens[start]))
			i++;
		start++;
	}
	return (i);
}

char	**fill_oprators(char **dst, char **tokens, int start, int end)
{
	int	i;

	i = 0;
	while (tokens[start] && start < end)
	{
		if (is_redirection(tokens[start]))
		{
			dst[i] = tokens[start];
			i++;
		}
		start++;
	}
	dst[i] = NULL;
	return (dst);
}
