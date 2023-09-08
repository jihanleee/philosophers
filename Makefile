# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 02:52:38 by jihalee           #+#    #+#              #
#    Updated: 2023/09/08 18:47:27 by jihalee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = ./srcs/

INCLUDE = -I ./include/

SRCS = ft_calloc.c ft_atol.c main.c mutex.c

SRC_FILES = $(addprefix $(SRC_DIR), $(SRCS))

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc

CFLAGS = -Wextra -Werror -Wall -g

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ #-fsanitize=thread

$(NAME) : $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES) $(INCLUDE) -pthread -g #-fsanitize=thread

clean :
	rm -f *.o */*.o 

fclean : clean
	rm -f $(NAME) $(LIBFT)

re : fclean all

.PHONY : clean fclean all re
