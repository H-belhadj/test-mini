/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:32:20 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 17:34:36 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(char *sep)
{
	char	*tmp;
	int		fds[2];

	pipe(fds);
	while (1)
	{
		tmp = readline("herdoc> ");
		if (!tmp)
			break ;
		if (strcmp(tmp, sep) == 0)
			break ;
		ft_putendl_fd(tmp, fds[1]);
		free(tmp);
	}
	close(fds[1]);
	return (fds[0]);
}

void	insertion(int redir_type, t_cmd *cmd, int *fd, int i)
{
	if (redir_type == INSERT || redir_type == INSERT_FROM)
	{
		i = 0;
		while (cmd->files[i])
		{
			*fd = open(cmd->files[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (cmd->files[i + 1] != NULL)
				close(*fd);
			i++;
		}
		cmd->fd_out = *fd;
	}
	else if (redir_type == INSERT_FROM)
	{
		i = 0;
		while (cmd->files[i])
		{
			*fd = open(cmd->files[i], O_RDONLY, 0644);
			if (cmd->files[i + 1] != NULL)
				close(*fd);
			i++;
		}
		cmd->fd_in = *fd;
	}
}

int	open_redir(t_cmd *cmd)
{
	int	i;
	int	fd;
	int	redir_type;

	fd = -1;
	redir_type = get_redir_type(cmd);
	if (redir_type == INSERT || redir_type == INSERT_FROM)
		insertion(redir_type, cmd, &fd, 0);
	else if (redir_type == APPEND)
	{
		i = -1;
		while (cmd->files[++i])
		{
			fd = open(cmd->files[i], O_RDWR | O_CREAT | O_APPEND, 0644);
			if (cmd->files[i + 1] != NULL)
				close(fd);
		}
		cmd->fd_out = fd;
	}
	else if (redir_type == HEREDOC)
	{
		fd = read_heredoc(cmd->files[0]);
		cmd->fd_in = fd;
	}
	return (fd);
}

void	child_exec(t_data_cmd *cmd, char *path, char **env)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (path == 0 || str_cmp(cmd->cmds[0].cmd_args[0], ""))
	{
		ft_putstr_fd("Command Not Found\n", 2);
		exit(127);
	}
	if (cmd->cmds->fd_in > 0)
	{
		dup2(cmd->cmds->fd_in, 0);
		close(cmd->cmds->fd_in);
	}
	if (cmd->cmds->fd_out > 0)
	{
		dup2(cmd->cmds->fd_out, 1);
		close(cmd->cmds->fd_out);
	}
	if (execve(path, cmd->cmds->cmd_args, env) == -1)
	{
		ft_putstr_fd("execve Error\n", 2);
		exit(126);
	}
}

void	execut_all(t_data_cmd *vars, char **env)
{
	if (vars->cmd_size == 1)
		execute_siple(vars, env);
	else
		execute_compund(vars);
}
