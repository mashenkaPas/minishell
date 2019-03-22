# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpas <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/19 18:04:36 by mpas              #+#    #+#              #
#    Updated: 2019/03/15 14:13:01 by mpas             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=address
DEPS = includes
LIBS = libft/libft.a b_printf/libftprintf.a
SRC = main.c srcs/a_execution.c srcs/c_built_functions.c srcs/d_built_functions.c srcs/e_split.c srcs/f_split_functions.c \
srcs/g_manage_dollar.c srcs/h_tilda.c srcs/i_env_functions.c srcs/j_env_funcioins.c srcs/k_env_functioins.c 
OBJ = $(SRC:.c=.o)

all: libftcreate b_printfcreate $(NAME)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)

libftcreate:
	@$(MAKE) -C ./libft

b_printfcreate:
	@$(MAKE) -C ./b_printf

clean:
	@$(MAKE) clean -C ./libft 
	@$(MAKE) clean -C ./b_printf
	@/bin/rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C ./libft 
	@$(MAKE) fclean -C ./b_printf
	@/bin/rm -f $(NAME)

re: fclean all
