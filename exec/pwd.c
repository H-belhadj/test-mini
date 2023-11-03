/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:49:31 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/11/03 22:01:35 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	(void) cmd;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	s_help.exit_status = 0;
}
