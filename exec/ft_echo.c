/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:53:17 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/03 21:50:25 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	while (cmd->cmd_args[i])
	{
		if (ft_strncmp(cmd->cmd_args[i], "-n", 2) == 0)
			flag = 0;
		else
			break ;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		ft_putstr_fd(cmd->cmd_args[i], 1);
		i++;
		if (cmd->cmd_args[i])
			write(1, " ", 1);
	}
	if (flag)
		write(1, "\n", 1);
}
