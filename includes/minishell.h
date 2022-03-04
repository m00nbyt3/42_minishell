/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:43:29 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/04 17:31:31 by ycarro           ###   ########.fr       */
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
typedef struct	s_totems
{
	char	*content;
	char	**flags; //Liberar!!!
	int		fd;
	char	type; 
	//i->stdi o->stdo e->sterr a->args c->command
	//u->until p->append
	int		section; 
	struct s_totems	*next;
}				t_totems;

//Functions
t_list		*store_env_in_list(char **environ);
void		ft_builtins(char *input, t_list **env);
void		ft_env(t_list **env);
void		ft_chk_quotes(t_list *args);
t_totems	*sp_split(char *s);
char		*new_element(char *s, t_totems **input);
int			is_special_c(char *str, t_totems *totem, int i);
char		*remove_quotes(char *str);
void		ft_add_totem(t_totems **input, t_totems *new);
void		ft_print_totems(t_totems *input);
void		ft_clear_input(t_totems **lst, void (*del)(void *));

#endif

