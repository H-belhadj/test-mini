/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:18:03 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 14:13:02 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_compund(t_data_cmd *cmd)
{
    int     pid;
    int     save;
    int     i;
    int     fd[2];
    char    *path;

    fd[0] = -1;
    fd[1] = -1;
    save = -1;
    i = -1;
    
    while (++i < cmd->cmd_size) 
    {
        if (i != cmd->cmd_size - 1)
        {
            if(pipe(fd) == -1)
            {
                printf("Error \n");
                exit(127);
            }
        }
        
        pid = fork();
        if (pid == 0)
        { 
            // signal(SIGQUIT, SIG_DFL);
	        // signal(SIGINT, SIG_DFL);
            if (i == 0 && fd[1] != -1)
                dup2(fd[1], STDOUT_FILENO);
            else if (i == cmd->cmd_size - 1 && save != -1)
                dup2(save, STDIN_FILENO);
            else if (i < cmd->cmd_size - 1 && i > 0 && save != -1 && fd[1] != -1)
            {
                dup2(save, STDIN_FILENO);
                dup2(fd[1], STDOUT_FILENO);
            }
            if (save != -1)
                close(save);
            if (fd[0] != -1)
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);
                
            path = get_path(cmd->cmds[i].cmd_args[0], cmd);
            if (path)
            {
                execve(path, cmd->cmds[i].cmd_args, NULL);
                ft_putstr_fd("Error\n", 2);
                exit(1);
            }
            exit(1);
        }

        if (pid > 0)
        {
            close(save);
            save = fd[0];
            close(fd[1]);
            fd[0] = -1;
            fd[1] = -1;
        }
    }
    close(save);
    char raw_status[4];
    waitpid(pid, (int *)raw_status, 0);
    printf("%d %d %d %d\n", raw_status[0], raw_status[1], raw_status[2], raw_status[3]);
    if (raw_status[0])
        s_help.exit_status = raw_status[0] + 128;
    else
        s_help.exit_status = raw_status[1];
    while (waitpid(-1, NULL, 0) != -1)
        ;
}
