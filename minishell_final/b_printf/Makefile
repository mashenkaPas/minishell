# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpas <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/17 13:02:02 by mpas              #+#    #+#              #
#    Updated: 2018/12/03 21:05:44 by mpas             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
HEADER = libftprintf.h

CFILES = src/ft_itoa_base.c src/b_printf.c src/ft_putchar_a.c src/ft_putstr_a.c src/ft_strlen_a.c
OFILES = *.o

all: $(NAME)

$(NAME):
	@echo "b_printf compiling..."
	@gcc $(CFLAGS) -I$(HEADER) -c $(CFILES) 
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OFILES)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
