/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:43:36 by omakran           #+#    #+#             */
/*   Updated: 2023/11/07 18:02:09 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_eligible_to_expand_one(char *token, t_count_tokens *count)
{
	while (token[count->i])
	{
		if (token[count->i] == '\'' && (count->d_q % 2 == 0))
			(count->s_q)++;
		if (token[count->i] == '\"' && (count->s_q % 2 == 0))
			(count->d_q)++;
		if (token[count->i] == '$' && count->s_q % 2 == 0)
			return (1);
		(count->i)++;
	}
	return (0);
}

int	is_eligible_to_expand(char *token, int stop, int in)
{
	t_count_tokens	count;

	count.i = 0;
	count.s_q = 0;
	count.d_q = 0;
	if (in)
	{
		if (is_eligible_to_expand_one(token, &count) == 1)
			return (1);
	}
	else
	{
		while (token[count.i])
		{
			if (token[count.i] == '\'' && (count.d_q % 2 == 0))
				count.s_q++;
			if (token[count.i] == '\"' && (count.s_q % 2 == 0))
				count.d_q++;
			if ((stop == count.i && token[count.i] == '$') && count.s_q
				% 2 == 0)
				return (1);
			count.i++;
		}
	}
	return (0);
}

int	var_size(char *token, int start)
{
	int	size;

	size = 0;
	while (token[start] && ft_isalpha(token[start]))
	{
		start++;
		size++;
	}
	return (size);
}

char    *expand(char *token)
{
    int        i;
    char    *tmp;
    char    *tmp2;
    char    *var_name;
    char    *var_value;

    i = 0;
    while (token[i])
    {
        if (is_eligible_to_expand(token, i, 0))
        {
            tmp = ft_substr(token, 0, i);
            if (token[i + 1] && token[i + 1] == '?') {
                var_value = ft_itoa(s_help.exit_status);
                i++;
            }
			else
			{
                var_name = ft_substr(token, i + 1, var_size(token, i + 1));
                var_value = getenv(var_name);
                if (!var_value)
                    var_value = "";
            }
            tmp2 = ft_strjoin(var_value, (&token[i + 1 + var_size(token, i
                            + 1)]));
            token = ft_strjoin(tmp, tmp2);
            i = 0;
        }
        else
            i++;
    }
    token [i] = '\0';
    return (token);
}

char	**expand_all_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_eligible_to_expand(tokens[i], 0, 1))
			tokens[i] = expand(tokens[i]);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
