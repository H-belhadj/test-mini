/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:49:22 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 16:20:13 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_free_node(Node *cur)
{
	free(cur->key);
	free(cur->value);
	free(cur);
}

void	part1(Node *cur, Node *prev, char *key)
{
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

void	part2(Node **head, Node *cur)
{
	*head = cur->next;
	_free_node(cur);
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
				part2(head, cur);
				continue ;
			}
			prev = cur;
			part1(cur, prev, key);
		}
	}
}
