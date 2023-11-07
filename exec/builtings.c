/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:30:28 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/07 17:41:17 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_in(t_data_cmd *vars)
{
	if (open_redir(vars->cmds) > 0)
		if (vars->cmds->fd_in > 0)
			dup2(vars->cmds->fd_in, 0);
	if (vars->cmds->fd_out > 0)
		dup2(vars->cmds->fd_out, 1);
	if (str_cmp(vars->cmds[0].cmd_args[0], "exit"))
		ft_exit(&vars->cmds[0]);
	else if (str_cmp(vars->cmds[0].cmd_args[0], "echo"))
		ft_echo(&vars->cmds[0]);
	else if (str_cmp(vars->cmds[0].cmd_args[0], "pwd"))
		ft_pwd(&vars->cmds[0]);
	else if (str_cmp(vars->cmds[0].cmd_args[0], "env"))
		ft_print_env(vars->envp);
	else if (str_cmp(vars->cmds[0].cmd_args[0], "cd"))
		cd(&vars->cmds[0], vars);
	else if (str_cmp(vars->cmds[0].cmd_args[0], "export"))
		export(&vars->envp, vars->cmds[0].cmd_args);
	else if (str_cmp(vars->cmds[0].cmd_args[0], "unset"))
		ft_unset2(vars->envp, vars->cmds[0].cmd_args);
	else
		return (1);
	return (0);
}

int	execut_builting(t_data_cmd *vars)
{
	int	rfd;
	int	wfd;

	rfd = dup(0);
	wfd = dup(1);
	if (build_in(vars))
	{
		dup2(rfd, 0);
		dup2(wfd, 1);
		close(rfd);
		close(wfd);
		return (0);
	}
	dup2(rfd, 0);
	dup2(wfd, 1);
	close(rfd);
	close(wfd);
	return (1);
}

void	execute_siple(t_data_cmd *cmd, char **env)
{
	int		pid;
	char	*path;
	int		status;

	status = 0;
	if (execut_builting(cmd))
		return ;
	if (cmd->cmds->cmd_args[0] == NULL)
		return ;
	path = get_path(cmd->cmds[0].cmd_args[0], cmd);
	if (str_cmp(cmd->cmds[0].cmd_args[0], "./minishell"))
		path = "./minishell";
	pid = fork();
	if (pid == 0)
		child_exec(cmd, path, env);
	else
	{
		if (cmd->cmds->fd_in > 0)
			close(cmd->cmds->fd_in);
		if (cmd->cmds->fd_out > 0)
			close(cmd->cmds->fd_out);
		waitpid(pid, &status, 0);
	}
	s_help.exit_status = status / 256;
}
