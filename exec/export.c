/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:52:40 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 16:58:09 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_export_key(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}

char	*get_export_value(char *arg, int key_length)
{
	int	value_length;

	if (arg[key_length] == 0)
		return (NULL);
	value_length = ft_strlen(arg) - key_length - 1;
	return (ft_substr(arg, key_length + 1, value_length));
}

void	export_help(Node **head, char *args, char *key)
{
	Node	*entry;
	char	*value;

	value = get_export_value(args, ft_strlen(key));
	entry = get_env_entry(*head, key);
	if (entry)
	{
		free(key);
		if (value)
		{
			free(entry->value);
			entry->value = value;
		}
	}
	else
		lstadd_back(head, lst_new(key, value));
	if (*head)
		lst_new(key, value);
	else
		lstadd_back(head, lst_new(key, value));
}

void	export(Node **head, char **args)
{
	char	*key;
	int		i;

	if (args[1] == NULL)
	{
		get_env_export(*head);
		return ;
	}
	i = 0;
	while (args[++i])
	{
		key = get_export_key(args[i]);
		if (!is_key_valid(key))
		{
			printf("'%s' is not a valid identifier.\n", args[i]);
			break ;
		}
		export_help(head, args[i], key);
	}
}
