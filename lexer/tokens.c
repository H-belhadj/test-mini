/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:37:16 by omakran           #+#    #+#             */
/*   Updated: 2023/11/01 16:54:31 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_sequel(t_count_tokens *count, char *line)
{
	count->token_size = count_tokens(line);
	count->new_tokens = ft_malloc(sizeof(char *) * ((count->token_size) + 1), 0,
			ALLOC, 0);
	if (!count->new_tokens)
		exit(1);
	count->d_q = 0;
	count->s_q = 0;
	count->i = 0;
	count->space_tab = "\t ";
	count->pip_redi = "<>|";
	count->arg_size = 0;
	count->dst_counter = 0;
}

void	tokens_two(t_count_tokens *count, char *line)
{
	count->arg_size = 0;
	if (line[count->i] == '\'')
	{
		count->arg_size++;
		count->s_q++;
	}
	if (line[count->i] == '\"')
	{
		count->arg_size++;
		count->d_q++;
	}
}

void	token_three(t_count_tokens *count, char *line)
{
	while (1)
	{
		if (!line[count->i + count->arg_size])
			break ;
		if (line[count->i + count->arg_size] && line[count->i \
			+ count->arg_size] == '\'')
			count->s_q++;
		else if (line[count->i + count->arg_size] && line[count->i \
			+ count->arg_size] == '\"')
			count->d_q++;
		if (line[count->i + count->arg_size] && ((ft_search(count->pip_redi,
						line[count->i + count->arg_size])
					|| ft_search(count->space_tab, line[count->i \
						+ count->arg_size])) && (is_odd(count->s_q)
					&& is_odd(count->d_q))))
			break ;
		count->arg_size++;
	}
}

char	**tokens(char *line)
{
	t_count_tokens	count;

	tokens_sequel(&count, line);
	while (line[count.i])
	{
		tokens_two(&count, line);
		token_three(&count, line);
		count.token_str = get_elemnts(count.i, count.arg_size, line);
		if (!is_only_space_and_tab(count.token_str))
			count.new_tokens[count.dst_counter++] = count.token_str;
		if (ft_search("<>", line[count.i + count.arg_size]))
		{
			count.new_tokens[count.dst_counter++] = split_redirections(count.i
					+ count.arg_size, line);
			count.arg_size += ft_strlen(split_redirections(count.i
						+ count.arg_size, line)) - 1;
		}
		else if (ft_search("|", line[count.i + count.arg_size]))
			count.new_tokens[count.dst_counter++] = "|";
		count.i += count.arg_size;
		count.i++;
	}
	count.new_tokens[count.dst_counter] = 0;
	return (count.new_tokens);
}
