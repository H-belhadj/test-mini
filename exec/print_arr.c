/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:26:20 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 17:28:17 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		printf("arr[%d]: %s\n", i, arr[i]);
}

bool	is_key_valid(char *key)
{
	int	i;

	i = 0;
	if (key[0] == 0)
		return (false);
	if (!(key[0] == '_' || isalpha(key[0])))
		return (false);
	while (key[++i])
	{
		if (!(key[i] == '_' || isalnum(key[i])))
			return (false);
	}
	return (true);
}

char	*get_key(Node *envp, char *key)
{
	while (envp)
	{
		if (strcmp(envp->key, key) == 0)
			return (key);
		envp = envp->next;
	}
	return (NULL);
}

Node	*get_env_entry(Node *envp, char *key)
{
	while (envp)
	{
		if (strcmp(envp->key, key) == 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

int	get_redir_type(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->operators[++i])
	{
		if (ft_strlen(cmd->operators[i]) == 2)
		{
			if (!ft_strncmp(cmd->operators[i], ">>",
					ft_strlen(cmd->operators[i])))
				return (APPEND);
			else if (!ft_strncmp(cmd->operators[i], "<<",
					ft_strlen(cmd->operators[i])))
				return (HEREDOC);
		}
		else
		{
			if (!ft_strncmp(cmd->operators[i], ">",
					ft_strlen(cmd->operators[i])))
				return (INSERT);
			else if (!ft_strncmp(cmd->operators[i], "<",
					ft_strlen(cmd->operators[i])))
				return (INSERT_FROM);
		}
	}
	return (-1);
}
