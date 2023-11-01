/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:24:21 by omakran           #+#    #+#             */
/*   Updated: 2023/11/01 16:32:27 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
// # include </goinfre/hbelhadj/.brew/opt/readline/include>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>

struct s_help
{
	int exit_status;
}s_help;

enum e_redir_types {
	INSERT, // >
	APPEND, // >>
	HEREDOC, // <<
	INSERT_FROM,
};

typedef struct s_cmd
{
	char	**cmd_args;
	char	**operators;
	char	**files;
	int		next_is_pipe;
	int		fd_in;
	int		fd_out;
}			t_cmd;

typedef struct Node {
    char    *key;
    char    *value;
    struct Node* next;
} Node;

typedef struct s_u
{
	char		*line;
	char		**_tokens;
	char		**gg;
	char		*trimed_line;
}	t_u;
typedef struct s_data_cmds
{
	t_cmd	*cmds;
	Node	*envp;
	int		cmd_size;
	char	*line;
	char	**_tokens;
	char	**gg;
	char	*trimed_line;
}			t_data_cmd;

typedef struct s_count_tokens
{
	int		i;
	int		d_q;
	int		s_q;
	int		count_words;
	int		arg_size;
	int		dst_counter;
	int		token_size;
	char	*space_tab;
	char	*pip_redi;
	char	*token_str;
	char	**new_tokens;
}			t_count_tokens;

typedef struct s_sort_cmds
{
	int		i;
	int		c;
	int		k;
	int		counter;
	int		tmp;
	int		cmd_size;
	t_cmd	*cmds;
}			t_sort_cmds;

/*###################### Helpers Functions: ####################*/

t_cmd		*sort_cmds(char **args, t_data_cmd *vars);
int			count_opertors_and_file(char **tokens, int start, int end);
int			count_cmds(char **tokens);
int			is_redirection(char *str);
int			str_cmp(char *s1, char *s2);
int			count_tokens(char *line);
int			ft_search(char *str, char c);
int			is_odd(int nbr);
int			is_only_space_and_tab(char *str);
int			count_tokens(char *line);
char		*get_elemnts(int start, int length, char *str);
char		*split_redirections(int start, char *str);
char		*expand(char *token);
char		**tokens(char *line);
char		**expand_all_tokens(char **tokens);
char		**remove_quotes(char **tokens);
char		**fill_commads(char **dst, char **tokens, int start, int end);
char		**fill_oprators(char **dst, char **tokens, int start, int end);
void		initialize_fnct(t_count_tokens *count);
void		count_token_two(t_count_tokens *count, char *line);
void		count_token_sequel(t_count_tokens *count, char *line);
void    cd(t_cmd *cmd, t_data_cmd *vars);
void	get_env_export(Node *envp);
Node	*lst_new(char *key, char *value);
void	lstadd_back(Node** head,Node *new_node);
void    _free(char **array);
Node	*ft_env(char **env);
void    ft_print_env(Node *envp);
int		get_redir_type(t_cmd *cmd);
int		read_heredoc(char *sep);
int		open_redir(t_cmd *cmd);
void	execute_siple(t_data_cmd *cmd, char **env);
void	execut_all(t_data_cmd *vars, char **env);
int		execut_builting(t_data_cmd *vars);
int		digit(char *str);
int		ft_exit_short(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
void   	print_arr(char **arr);
char	*get_key(Node *envp, char *key);
void    export(Node* envp, char **str);
void	ft_echo(t_cmd *cmd);
char	*ft_getenv(char *str, t_data_cmd *vars);
char	*get_path(char *cmd, t_data_cmd *vars);
void	execute_compund(t_data_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void    ft_unset(Node* envp, char *str);
/*#################################################################*/

/*###################### ERRORS FUNCTIONS #########################*/

int			syntax_errors(t_cmd *syntax, char **tokens);

/*#################################################################*/

#endif