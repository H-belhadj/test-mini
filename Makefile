# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 15:36:17 by omakran           #+#    #+#              #
#    Updated: 2023/11/07 17:54:43 by hbelhadj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCE = ./lexer/tokens.c ./parser/sort_cmds.c  cmp.c  ./parser/expand.c ./parser/remove_quotes.c \
		./lexer/errors.c ./lexer/utls_tokens.c ./lexer/utls_tokens_two.c ./parser/utls_sort_cmds.c allocation_denamic/ft_malloc.c \
		allocation_denamic/misc_functions.c allocation_denamic/misc_functions2.c \
		./exec/cd.c ./exec/env_export.c ./exec/env.c ./exec/execut.c ./exec/exit.c ./exec/export.c ./exec/ft_echo.c ./exec/ft_getenv.c ./exec/path.c ./exec/pipes.c ./exec/pwd.c ./exec/unset.c ./exec/ft_substr.c ./exec/print_arr.c ./exec/builtings.c

CC = cc

#brew install readline
CFLAGS = -Wall -Wextra -Werror -I. #-fsanitize=address -g 

READLINE =  -L/Users/hbelhadj/.brew/opt/readline/lib -lreadline -I/Users/hbelhadj/.brew/opt/readline/include/

OBJS = $(SOURCE:.c=.o)

RM = rm -rf

all: $(NAME)

LIBFT=libft_/libft.a
ALLOCATION=allocation_denamic/ft_malloc.a

%.o: %.c
	@$(CC) $(CFLAGS) -I/Users/hbelhadj/.brew/opt/readline/include/ -c $< -o $@

$(NAME): $(OBJS)
	@make -C libft_
	@$(CC) $(CFLAGS) minishell.c $(OBJS)  $(READLINE) $(LIBFT) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@make -C libft_ fclean

re: fclean all
	@make -C libft_ fclean

.PHONY: all clean fclean re
