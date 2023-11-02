/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakran <omakran@student.1337.ma >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:47:38 by omakran           #+#    #+#             */
/*   Updated: 2023/10/27 11:25:08 by omakran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_files(char **dst, char **tokens, int start, int end)
{
	int	i;

	i = 0;
	while (tokens[start] && start < end)
	{
		if ((start - 1 >= 0 && is_redirection(tokens[start - 1])))
		{
			dst[i] = tokens[start];
			i++;
		}
		start++;
	}
	dst[i] = NULL;
	return (dst);
}

void	sort_initialize(t_sort_cmds *sort, char **tokens)
{
	sort->cmd_size = count_cmds(tokens);
	sort->cmds = ft_malloc(sizeof(t_cmd) * (sort->cmd_size + 1), 0, ALLOC, 0);
	if (!sort->cmds)
		exit(1);
	sort->i = 0;
	sort->c = 0;
	sort->k = 0;
	sort->counter = 0;
	sort->tmp = 0;
}

void	sort_cmds_one(t_sort_cmds *sort, char **tokens)
{
	while (tokens[sort->counter] && !str_cmp(tokens[sort->counter], "|"))
	{
		if (sort->counter == 0 || ((sort->counter - 1 >= 0
					&& !is_redirection(tokens[sort->counter - 1]))
				&& !is_redirection(tokens[sort->counter])))
		{
			if (sort->counter == 0 && !is_redirection(tokens[sort->counter]))
				sort->i++;
			else if (sort->counter - 1 >= 0
				&& !is_redirection(tokens[sort->counter - 1])
				&& !is_redirection(tokens[sort->counter]))
				sort->i++;
		}
		sort->counter++;
	}
	if (tokens[sort->counter] && str_cmp(tokens[sort->counter], "|"))
		sort->cmds[sort->k].next_is_pipe = 1;
	else
		sort->cmds[sort->k].next_is_pipe = 0;
}

void	sort_cmds_two(t_sort_cmds *sort, char **tokens)
{
	sort->cmds[sort->k].cmd_args = ft_malloc(sizeof(char *) * (sort->i + 1), 0,
			ALLOC, 0);
	sort->cmds[sort->k].cmd_args = fill_commads(sort->cmds[sort->k].cmd_args,
			tokens, sort->tmp, sort->counter);
	sort->cmds[sort->k].operators = ft_malloc(sizeof(char *)
			* (count_opertors_and_file(tokens, sort->tmp, sort->counter) + 1),
			0, ALLOC, 0);
	sort->cmds[sort->k].files = ft_malloc(sizeof(char *)
			* (count_opertors_and_file(tokens, sort->tmp, sort->counter) + 1),
			0, ALLOC, 0);
	sort->cmds[sort->k].operators = fill_oprators(sort->cmds[sort->k].operators,
			tokens, sort->tmp, sort->counter);
	sort->cmds[sort->k].files = fill_files(sort->cmds[sort->k].files, tokens,
			sort->tmp, sort->counter);
	if (!sort->cmds[sort->k].cmd_args || !sort->cmds[sort->k].operators
		|| !sort->cmds[sort->k].files)
		exit(1);
	if (tokens[sort->counter] && str_cmp(tokens[sort->counter], "|"))
		sort->counter += 1;
	sort->i = 0;
	sort->k++;
	sort->c++;
}

t_cmd	*sort_cmds(char **tokens, t_data_cmd *vars)
{
	t_sort_cmds	sort;

	sort_initialize(&sort, tokens);
	while (sort.c < sort.cmd_size)
	{
		sort.tmp = sort.counter;
		sort_cmds_one(&sort, tokens);
		sort_cmds_two(&sort, tokens);
	}
	vars->cmd_size = sort.cmd_size;
	return (sort.cmds);
}
