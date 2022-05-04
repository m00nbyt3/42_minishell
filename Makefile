# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 10:43:28 by agallipo          #+#    #+#              #
#    Updated: 2022/05/04 12:28:21 by ycarro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC := gcc

LIBFTDIR = libft/
INCLUDE :=  -I includes/
HEADERFILES := includes/minishell.h

SRCS :=	main.c \
		utils.c \
		builtins/builtins.c \
		builtins/cmds1.c \
		builtins/other.c \
		parse/quotes.c \
		parse/splitx.c \
		totem/manage.c \
		totem/flags.c \
		totem/elements.c \
		parse/transform.c \
		exec/env.c \
		exec/multiple.c \
		exec/childs.c \
		exec/cmds.c \
		exec/here_doc.c \
		exec/error.c

OBJS := $(SRCS:%.c=obj/%.o)

CFLAGS := $(INCLUDE) -I $(HOME)/.brew/opt/readline/include -fsanitize=address -g # -Wall -Werror -Wextra #-fsanitize=address -g
LDFLAGS := -L/usr/include -lreadline -L $(HOME)/.brew/opt/readline/lib -Llibft -lft -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

obj/%.o: srcs/%.c $(HEADERFILES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	make -sC $(LIBFTDIR) clean
	rm -rf $(OBJS) libft.a

fclean: clean
	make -sC $(LIBFTDIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
