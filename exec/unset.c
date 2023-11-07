/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:49:22 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 16:05:18 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_free_node(Node *cur)
{
	free(cur->key);
	free(cur->value);
	free(cur);
}

void	ft_unset2(Node *envp, char **args)
{
	Node	**head;
	Node	*cur;
	Node	*prev;
	char	*key;
	int		i;

	head = &envp;
	i = 0;
	while (args[++i])
	{
		key = args[i];
		if (!is_key_valid(key))
			printf("invalid key");
		else
		{
			cur = envp;
			if (strcmp(cur->key, key) == 0)
			{
				*head = cur->next;
				_free_node(cur);
				continue ;
			}
			prev = cur;
			cur = cur->next;
			while (cur)
			{
				if (strcmp(cur->key, key) == 0)
				{
					prev->next = cur->next;
					_free_node(cur);
					break ;
				}
				prev = cur;
				cur = cur->next;
			}
		}
	}
}
