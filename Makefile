# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 02:52:38 by jihalee           #+#    #+#              #
#    Updated: 2023/05/05 17:13:34 by jihalee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c print_formats1.c print_formats2.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wextra -Werror -Wall

INCLUDE = ./

all : ${NAME}

.c.o :
	${CC} ${CFLAGS} -c $< -o $@

$(NAME) : ${OBJS}
	ar -rcs ${NAME} ${OBJS}

clean :
	rm -f *.o

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : clean fclean all re
