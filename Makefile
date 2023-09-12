# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 02:52:38 by jihalee           #+#    #+#              #
#    Updated: 2023/09/13 00:59:25 by jihalee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = ./srcs/

INCLUDE = -I ./include/

SRCS = lib_func.c main.c utils.c routine1.c routine2.c mutex.c

SRC_FILES = $(addprefix $(SRC_DIR), $(SRCS))

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc

CFLAGS = -Wextra -Werror -Wall -g

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(INCLUDE) -pthread

clean :
	rm -f *.o */*.o 

fclean : clean
	rm -f $(NAME) $(LIBFT)

re : fclean all

.PHONY : clean fclean all re
