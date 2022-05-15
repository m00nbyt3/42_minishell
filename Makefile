# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 10:43:28 by agallipo          #+#    #+#              #
#    Updated: 2022/05/15 16:55:00 by ycarro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC := gcc

LIBFTDIR = libft/
INCLUDE :=  -I includes/
HEADERFILES := includes/minishell.h

SRCS :=	main.c \
		utils.c \
		utils2.c \
		builtins/builtins.c \
		builtins/exit.c \
		builtins/other.c \
		builtins/export.c \
		builtins/echo.c \
		builtins/cd_pwd.c \
		builtins/unset.c \
		parse/quotes.c \
		parse/quotes2.c \
		parse/splitx.c \
		parse/environ.c \
		parse/check_reds_pipes.c \
		totem/manage.c \
		totem/flags.c \
		totem/elements.c \
		totem/dollars.c \
		parse/transform.c \
		parse/manage.c \
		exec/env_commands.c \
		exec/multiple.c \
		exec/childs.c \
		exec/cmds.c \
		exec/here_doc.c \
		exec/error.c \
		signals.c

OBJS := $(SRCS:%.c=obj/%.o)

CFLAGS := $(INCLUDE) -I $(HOME)/.brew/opt/readline/include -Wall -Werror -Wextra #-fsanitize=address -g
LDFLAGS := -L/usr/include -lreadline -L $(HOME)/.brew/opt/readline/lib -Llibft -lft

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
