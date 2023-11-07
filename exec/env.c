/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:14:39 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 15:41:13 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

Node	*lst_new(char *key, char *value)
{
	Node	*new_node;

	new_node = (Node *)ft_calloc(1, sizeof(Node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

// Function to add a new node to the back of a linked list
void	lstadd_back(Node **head, Node *new_node)
{
	Node	*current;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
}

void	_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

Node	*ft_env(char **env)
{
	int		i;
	Node	*head;
	char	**arr;

	head = NULL;
	i = 0;
	if (!env)
		exit(127);
	while (env[i])
	{
		arr = ft_split(env[i], '=');
		lstadd_back(&head, lst_new(ft_strdup(arr[0]), ft_strdup(arr[1])));
		_free(arr);
		i++;
	}
	return (head);
}

void	ft_print_env(Node *envp)
{
	while (envp)
	{
		printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
}
