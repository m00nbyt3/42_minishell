# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 10:43:28 by agallipo          #+#    #+#              #
#    Updated: 2022/02/25 16:04:32 by agallipo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c \
	   srcs/environ.c \
	   srcs/builtins.c \
	   #rcs/error.c srcs/env.c srcs/multiplepipes.c

OBJS = ${SRCS:.c=.o}

CFLAGS = # -Wall -Werror -Wextra #-fsanitize=address -g
LDFLAGS = -L/usr/include -lreadline

CC = gcc

INCLUDES = includes/

LIBFTDIR = libft/

NAME = minishell

RM = rm -fr

all:	 ${NAME}

${NAME}: ${OBJS}
	make -C ${LIBFTDIR}
	${CC} ${CFLAGS} ${LDFLAGS} ${OBJS} -I ${INCLUDES} -Llibft -lft -o ${NAME} 

%.o: %.c
	${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

clean:
			make -sC ${LIBFTDIR} clean
			${RM} ${OBJS} libft.a

fclean: clean

			make -sC ${LIBFTDIR} fclean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

