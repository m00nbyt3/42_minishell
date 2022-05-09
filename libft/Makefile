# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 13:59:32 by agallipo          #+#    #+#              #
#    Updated: 2022/05/09 15:43:51 by ycarro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strnstr.c \
			ft_putnbr_base.c\
			get_next_line.c\
			ft_free_matrix.c\
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_print_lst.c \
			ft_strcmp.c \
			ft_mtxdup.c \
			ft_mtxlen.c \
			ft_mtxjoin.c \
			ft_mtxcat.c

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(BONUS:.c=.o)
NAME	= libft.a
RM		= rm -f
FLAGS	= -Wall -Wextra -Werror -c
$(NAME): $(SRCS)
		@echo [Compiling libft...]
		@gcc $(FLAGS) $(SRCS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)
bonus:		$(OBJS) $(OBJS_B)
			@gcc $(FLAGS) $(SRCS)
			@ar rc $(NAME)
			@ranlib $(NAME)
			@echo [Done compiling libft :)]

all:		$(NAME)
clean:
			$(RM) $(OBJS)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all
.PHONY:     bonus all clean fclean re
