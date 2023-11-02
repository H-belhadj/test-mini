/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakran <omakran@student.1337.ma >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:49:22 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/02 16:31:02 by omakran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void    ft_unset(Node* envp, char *str)// char **args
// {
//     char **arr;
//     Node *tmp;
//     Node    *tmp1;

//     tmp = envp;
//     arr = ft_split(str, '=');
//     envp = envp->next;
//     while(envp)
//     {
//         if(strcmp(envp->key, arr[0]) == 0)
//         {
//             tmp1 = envp->next;
//             free(envp->key);
//             free(envp->value);
//             free(envp);
//             tmp->next = tmp1;
//             break; 
//         }
//         tmp = tmp->next;
//         envp = envp->next;
//     }
//     _free(arr);
// }

void    ft_unset2(Node* envp, char **args)
{
    Node    **head;
    Node    *cur;
    Node    *prev;
    char    *key;
    int     i;
    
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
                free(cur->key);
                free(cur->value);
                free(cur);
                continue;
            }
            prev = cur;
            cur = cur->next;
            while (cur)
            {
                if (strcmp(cur->key, key) == 0)
                {
                    prev->next = cur->next;
                    free(cur->key);
                    free(cur->value);
                    free(cur);
                    break;
                }
                prev = cur;
                cur = cur->next;
            }
        }
    }
}