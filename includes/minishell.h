/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:43:29 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/02 19:33:35 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ_END 0
# define WRITE_END 1

//Headers
# include "readline/readline.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

//Structs
typedef struct	s_totem_old
{
	char	*input;
	char	**flags;
	int		fd;
	int		type; //0->stdi 1->stdo 2->sterr 3->args 4->parse
}				t_totem_old;

typedef struct	s_totems
{
	char	*content;
	int		type;
	struct s_totems	*next;
}				t_totems;

//Functions
t_list		*store_env_in_list(char **environ);
void		ft_builtins(char *input, t_list **env);
void		ft_env(t_list **env);
void		ft_chk_quotes(t_list *args);
t_totems	*sp_split(char *s);
void		new_element (char *s, t_totems **input);
void		ft_add_totem(t_totems **input, t_totems *new);
void		ft_print_totems(t_totems *input);
void		ft_clear_input(t_totems **lst, void (*del)(void *));

#endif

