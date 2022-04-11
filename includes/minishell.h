/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:43:29 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/11 16:25:10 by ycarro           ###   ########.fr       */
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
	char					*heredoc;
	char					*append;
	struct s_transformer	*next;
}				t_transformer;

typedef struct s_oncreate
{
	int		section;
	int		inquotes;
	char	qtype;
}				t_oncreate;

typedef struct s_tools
{
	int			**fd;
	int			*pid;
	int			npipes;
	t_totems	*input;
	t_list		*envlist;
}				t_tools;

//Functions

//Utils
t_list			*store_env_in_list(char **environ);
void			run_cmd(char *complete, char **env);

//Builtins
int				ft_builtins(t_transformer *runner, char **env);
int				select_cmd(t_transformer *runner, char **env, int ofdin, int ofdout);
void			ft_echo(t_transformer *runner);
void			ft_cd(t_transformer *runner, char **env);
void			ft_pwd(void);
void			set_fds(t_totems *input, int section);
char			*ft_srchlist_var(char *tofind, t_list **env);
char			*ft_vsrch_var(char *tofind, char **env);


//Totem
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

//Pipes
void			ft_pipes(t_transformer **contents, char **env, t_totems *input, \
				t_list *envlist);
void			ft_while_pipes(t_transformer *content, t_tools *tools, char **env);
void			ft_final_pipe(t_transformer *content, t_tools *tools, char **env, int i);
void			ft_exit_process(int condition, char *argv);
void			ft_frst_child_pipe(t_transformer *smth, char **env, int *fd);
void			ft_mid_child_pipe(t_transformer *smth, char **env, int *fd1, int *fd2);
void			ft_bastard(t_transformer *smth, char **env, int *fd1);
int				count_cmds(t_transformer *data);
int				single_cmd(int npipes, t_transformer *smth, char **env);
void			ft_execute(t_transformer *smth, char **env);
int				ft_check_directory(char **flags);
char			*ft_env_path(char **env, char *argv, char **flags);
char			**ft_path_split(char **env);
void			ft_print_error(char *error, char *arg);
void			ft_error(t_transformer *smth, int cond);
void			here_doc(t_transformer *content);

#endif
