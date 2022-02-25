# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 13:59:32 by agallipo          #+#    #+#              #
#    Updated: 2021/12/01 15:19:56 by agallipo         ###   ########.fr        #
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

BONUS =		ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(BONUS:.c=.o)
NAME	= libft.a
RM		= rm -f
FLAGS	= -Wall -Wextra -Werror -c
$(NAME): $(SRCS)
		echo [Compilando...]
		gcc $(FLAGS) $(SRCS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)
		echo [Compilado.]
bonus:		$(OBJS) $(OBJS_B)
			echo [Compilando bonus...]
			gcc $(FLAGS) $(SRCS) $(BONUS)
			ar rc $(NAME) $(OBJS_B)
			ranlib $(NAME)
			echo [Compilados.]
all:		$(NAME)
clean:
			$(RM) $(OBJS) $(OBJS_B)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all
.PHONY:     bonus all clean fclean re
