/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:38:06 by omakran           #+#    #+#             */
/*   Updated: 2023/11/07 14:36:56 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] && str_cmp(tokens[i], "|") && (tokens[i + 1]
				&& str_cmp(tokens[i + 1], "|")))
					return (1);

		else if (tokens[i] && str_cmp(tokens[i], "|") && !tokens[i + 1])
		{
			// printf("kajdsfjasakdjshh\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	chech_operators_and_files(t_cmd *syntax)
{
	int	i;

	i = 0;
	while (syntax->operators[i])
	{
		if (syntax->files[i] && str_cmp(syntax->files[i], ""))
			return (1);
		else if (syntax->files[i] && str_cmp(syntax->files[i], "<<"))
			return (1);
		else if (syntax->files[i] && str_cmp(syntax->files[i], ">>"))
			return (1);
		else if (syntax->files[i] && str_cmp(syntax->files[i], "<"))
			return (1);
		else if (syntax->files[i] && str_cmp(syntax->files[i], ">"))
			return (1);
		else if (!syntax->files[i])
			return (1);
		i++;
	}
	return (0);
}

int	syntax_errors(t_cmd *syntax, char **tokens)
{
	if (chech_operators_and_files(syntax) || check_pipes(tokens))
	{
		ft_putstr_fd("minishell : syntax error near unexpected token.\n", 2);
		return (1);
	}
	return (0);
}
