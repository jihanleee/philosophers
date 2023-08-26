# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 02:52:38 by jihalee           #+#    #+#              #
#    Updated: 2023/08/26 13:42:20 by jihalee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = ./srcs/

INCLUDE = -I ./include/

SRCS = main.c

SRC_FILES = $(addprefix $(SRC_DIR), $(SRCS))

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc

CFLAGS = -g -Wextra -Werror -Wall

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES) $(INCLUDE) -pthread

clean :
	rm -f *.o */*.o 

fclean : clean
	rm -f $(NAME) $(LIBFT)

re : fclean all

.PHONY : clean fclean all re
