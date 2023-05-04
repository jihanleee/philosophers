# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 02:52:38 by jihalee           #+#    #+#              #
#    Updated: 2023/05/04 18:34:44 by jihalee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a #ft_printf
LIBFT = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcat.c\
ft_strlcpy.c ft_tolower.c ft_toupper.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
ft_striter.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\

UTIL = print_formats.c

LIBFT_SRCS = $(addprefix ./libft/, $(LIBFT)) ft_printf.c

UTIL_SRCS = $(addprefix ./util/, $(UTIL))

SRCS = $(LIBFT_SRCS) $(UTIL_SRCS)

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wextra -Werror -Wall

INCLUDE = ./

all : ${NAME}

#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
#	gcc -nostartfiles -shared -o libft.so $(OBJS)

.c.o :
	${CC} ${CFLAGS} -c $< -o $@

$(NAME) : ${OBJS}
	ar -rcs ${NAME} ${OBJS}
	#$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) -o $(NAME)

clean :
	rm -f *.o

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : clean fclean all re
