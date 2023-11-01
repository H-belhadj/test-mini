/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_tokens_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakran <omakran@student.1337.ma >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:14:42 by omakran           #+#    #+#             */
/*   Updated: 2023/10/28 12:39:41 by omakran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_fnct(t_count_tokens *count)
{
	count->d_q = 0;
	count->s_q = 0;
	count->i = 0;
	count->space_tab = "\t ";
	count->pip_redi = "<>|";
	count->arg_size = 0;
	count->count_words = 0;
}

void	count_token_two(t_count_tokens *count, char *line)
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

void	count_token_sequel(t_count_tokens *count, char *line)
{
	count_token_two(count, line);
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

int	count_tokens(char *line)
{
	t_count_tokens	count;

	initialize_fnct(&count);
	while (line[count.i])
	{
		count_token_sequel(&count, line);
		count.token_str = get_elemnts(count.i, count.arg_size, line);
		if (!is_only_space_and_tab(count.token_str))
			count.count_words++;
		if (ft_search("<>", line[count.i + count.arg_size]))
			count.count_words++;
		else if (ft_search("|", line[count.i + count.arg_size]))
			count.count_words++;
		count.i += count.arg_size;
		count.i++;
	}
	return (count.count_words);
}
