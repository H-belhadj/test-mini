/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:24:18 by omakran           #+#    #+#             */
/*   Updated: 2023/11/02 17:01:46 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("TOKEN => %s\n", tokens[i]);
		i++;
	}
}

void	print_table_cmds(t_data_cmd *vars)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < vars->cmd_size)
	{
		c = 0;
		// printf("\n_____________________CMD [%d]_______________________\n", i);
		while (vars->cmds[i].cmd_args[c])
		{
			// printf("ARG[%d] => %s\n", c, vars->cmds[i].cmd_args[c]);
			c++;
		}
		c = 0;
		while (vars->cmds[i].operators[c])
		{
			// printf("OPERATOR[%d] => %s\nFILE[%d] => %s\n", c,
			// 	vars->cmds[i].operators[c], c, vars->cmds[i].files[c]);
			c++;
		}
		i++;
	}
}

// void	handler(int sig)
// {
// 	if (sig == SIGINT || sig == SIGQUIT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		return ;
// 	}
// }

int	handle_unclosed_quots(char *line)
{
	int	i;
	int	count_sq;
	int	count_dq;

	count_sq = 0;
	count_dq = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			count_sq++;
		if (line[i] == '\"')
			count_dq++;
		i++;
	}
	if (count_sq % 2 != 0 || count_dq % 2 != 0)
	{
		ft_putstr_fd("minishell : syntax error unclosed quots\n", 2);
		return (-1);
	}
	return (1);
}

int	main(int __unused argc, char __unused **argv, char __unused **env)
{
	t_data_cmd	*vars;
	t_u			data;


	if(argc != 1)
		return (1);
	// signal(SIGINT, handler);
	// signal(SIGQUIT, handler);
	vars = ft_malloc(sizeof(t_data_cmd), 0, ALLOC, 0);
	if (!vars)
		exit(1);
	vars->envp = ft_env(env); //you need to add this
	while (1)
	{
		data.line = readline("minishell$ ");
		if (!data.line)
			exit(127);
		data.trimed_line = ft_strtrim(data.line, "\n\t ");
		if (!data.trimed_line || !data.trimed_line[0])
			continue ;
		add_history(data.line);
		data.gg = tokens(data.line);
		data._tokens = expand_all_tokens(data.gg);
		data.gg = data._tokens;
		data._tokens = remove_quotes(data.gg);
		vars->cmds = sort_cmds(data._tokens, vars);
		print_table_cmds(vars);
		if(syntax_errors(&vars->cmds[0], data._tokens))
		{
			ft_malloc(0, 0, FREE_ALL, 0);
			free(data.line);
			continue ;
		}
		execut_all(vars, env);
		// ft_malloc(0, 0, FREE_ALL, 0);
		// free(data.line);
	}
	return (0);
}
