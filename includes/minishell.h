/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:43:29 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/24 11:32:31 by agallipo         ###   ########.fr       */
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
typedef struct s_totems
{
	char			*content;
	char			**flags;
	int				section;
	char			type;
	struct s_totems	*next;
}				t_totems;

typedef struct s_transformer
{
	char					*cmd;
	char					**flags;
	int						fdin;
	int						fdout;
	struct s_transformer	*next;
}				t_transformer;

typedef struct s_oncreate
{
	int		section;
	int		inquotes;
	char	qtype;
}				t_oncreate;

//Functions
t_list			*store_env_in_list(char **environ);
int				ft_builtins(t_totems *input, t_list **env);
void			ft_env(t_list **env);
void			ft_echo(t_totems *input, int section);
t_totems		*sp_split(char *s);
char			*char_detection(char *tmp, t_oncreate *shared, \
				t_totems *totem, int *i);
int				is_special_c(char *str, t_totems *totem, int i, \
				t_oncreate *shared);
int				is_redirection(char *str, t_totems *totem, int i);
void			set_command(t_totems *input, int sect);
char			*new_element(char *s, t_totems **input, t_oncreate *shared);
char			*set_totem_type(char *tmp, t_oncreate *shared, t_totems *totem);
int				ft_chk_quotes(char *str);
void			last_quote(char c, t_oncreate *shared);
char			*remove_quotes(char *str, t_oncreate *shared);
size_t			count_quotes(char *str, t_oncreate *shared);
void			ft_add_totem(t_totems **input, t_totems *new);
void			ft_print_totems(t_totems *input);
void			ft_clear_input(t_totems **lst, \
				void (*del)(void *));
void			vectorize_flags(t_transformer *runner, \
				t_totems *input, int sect);
int				count_flags(t_totems *input, int sect);
void			print_vector(t_transformer *runner);
t_transformer	*transform(t_totems *input);
void			ft_pipes(t_transformer **smtha, char **env, \
				t_totems *input, t_list *envlist);
char			*ft_env_path(char **env, char *argv, char **flags);
void			ft_exit_process(int condition, char *argv);
#endif
