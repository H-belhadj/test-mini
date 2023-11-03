/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:52:40 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/03 21:37:33 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	n;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	arr = ft_calloc(len + 1, sizeof(char));
	if (!arr)
		return (NULL);
	n = 0;
	while (n < len && s[start + n])
	{
		arr[n] = s[start + n];
		n++;
	}
	return (arr);
}

void    print_arr(char **arr)
{
    int i;

    i = -1;
    if (!arr)
        return ;
    while (arr[++i])
        printf("arr[%d]: %s\n", i, arr[i]);
}

char *get_key(Node *envp, char *key)
{
    while(envp)
    {
        if(strcmp(envp->key, key) == 0)
          return (key);          
        envp = envp->next;
    }
    return (NULL);
}

Node *get_env_entry(Node *envp, char *key)
{
    while(envp)
    {
        if(strcmp(envp->key, key) == 0)
          return (envp);          
        envp = envp->next;
    }
    return (NULL);
}

char    *get_export_key(char *arg)// key=value
{
    int i = 0;

    while (arg[i] && arg[i] != '=')
        i++;
    return (ft_substr(arg, 0, i));
}

bool is_key_valid(char *key)
{
    int i;

    if(key[0] == 0)
        return (false);

    if(!(key[0] == '_' || isalpha(key[0])))
        return (false);
    i = 0;
    while(key[++i])
    {
        if(!(key[i] == '_' || isalnum(key[i])))
            return (false);
    }
    return (true);
}
char    *get_export_value(char *arg, int key_length)
{
    int value_length;
    
    if (arg[key_length] == 0)
        return (NULL);
    value_length = ft_strlen(arg) - key_length - 1;
    return (ft_substr(arg, key_length + 1, value_length));
}

void    export(Node** head, char **args)
{
    Node    *entry;
    char    *key;
    char    *value;
    
    if(args[1] == NULL)
    {
        get_env_export(*head);
        return;
    }
    int i = 0;
    while(args[++i])
    {
        key = get_export_key(args[i]);
        if (!is_key_valid(key))
            printf("'%s' is not a valid identifier.\n", args[i]);
        
        value = get_export_value(args[i], ft_strlen(key));

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
        if(*head)
            lst_new(key, value);
        else
            lstadd_back(head, lst_new(key, value));
    }
    
}

