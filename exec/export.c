/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:52:40 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/01 17:38:21 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
    case 1;
        export a
    case 2:
        export a=word
        export a=
*/
char    *get_export_value(char *arg, int key_length)
{
    int value_length;
    
    if (arg[key_length] == 0)
        return (NULL);
    value_length = ft_strlen(arg) - key_length - 1;
    return (ft_substr(arg, key_length + 1, value_length));
}

void    export(Node* envp, char **args)// args => args
{
    Node    *entry;
    char    *key;
    char    *value;
    
    if(args[1] == NULL)
    {
        get_env_export(envp);
        return;
    }
    int i = 0;
    while(args[++i])
    {
        key = get_export_key(args[i]);
        /*
        what can the key contain
            -   only starts with _ or an alphabet
            -   only contains _ , alphabets and digits
        invalid keys:
            -   3lskdjf
            -   _lksdjf+
            -   (empty string/no key)
            -   +lksjdf
            -   jkhfkg.lfofof
        if (!is_key_valid(key))
            print not a valid identifier
        */
        value = get_export_value(args[i], ft_strlen(key));

        entry = get_env_entry(envp, key);

        //  if key already in env
        if (entry)
        {
            free(key);
            if (value)
            {
                free(entry->value);
                entry->value = value;    
            }
        }
        //  if key is not in env
        else
            lstadd_back(&envp, lst_new(key, value));
    }
    
}
