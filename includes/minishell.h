/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/15 16:41:21 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ_END 0
# define WRITE_END 1
# define SIGMINE 30

//Headers
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
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"

//Structs
typedef struct s_global
{
	int		ctr_c;
	int		ctr_b;
	int		ofdin;
	int		ofdout;
	int		exit_value;
	char	*pwd;
}				t_global;

typedef struct s_totems
{
	char			*content;
	char			**flags;
	int				section;
	char			type;
	char			qtype;
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
	char					qtype;
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

typedef struct s_env
{
	t_list	*list;
	char	**array;
	char	**export;
}				t_env;

//global
t_global	g_util;

//Functions
//Utils
void			sort_mtx(char **mtx);
char			*chr2str(char toadd, char *str, int *force);
void			set_origina_fd(void);
int				checkargs(t_transformer *runner, t_env *env);

//Parse
int				checkreds(char *str);
int				checkreds_2(char *str, int *smaller, int *bigger, int *first);
int				checkpipes(char *str, int count, int things, int err);
char			*set_quotes(char *str, t_oncreate *shared);
char			*inside_quote(char *str, char **tmp, t_oncreate *shared, \
	int *force);
//error
void			command_not_found(t_transformer *smth);

//environ
char			*get_my_env(char *name, char **env);
t_env			*basic_env(void);
char			**shell_level(char **env);
t_env			*store_environ(void);
t_list			*store_env_in_list(char **environ);

//Signals
void			sign(int sig);
void			ctrl_d(char *str);

//Builtins
int				ft_builtins(t_transformer *runner, t_env *env);
int				select_cmd(t_transformer *runner, t_env *env);
void			ft_echo(t_transformer *runner);
void			ft_cd(t_transformer *runner, char **env);
void			ft_pwd(void);
void			ft_builtin_exit(t_transformer *runner);
void			set_fds(t_totems *input, int section);
char			*ft_srchlist_var(char *tofind, t_list **env);
char			*ft_vsrch_var(char *tofind, char **env);
void			ft_print_mtx(char **env);
void			ft_print_export(char **env);
void			ft_export(t_transformer *orunner, t_env *env);
int				var_exist(char *str, char **environ, int i, int len);
char			**replace_env(char *toadd, char **environ);
char			**ft_export_add(t_transformer *runner, char **environ);
char			**ft_env_add(char *toadd, char **environ);
void			ft_unset(t_transformer *orunner, t_env *env);
char			**find_and_quit(char **env, char *var);
int				variable_match(char *var, char *name);
int				add_to_env(t_transformer *orunner);

//Totem
t_totems		*sp_split(char *s, char *used, size_t i, int j);
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
void			vectorize_flags(t_transformer *runner, t_totems *input, \
	int sect, t_env *env);
int				save_flag(t_totems *input, int sect, char **vector, t_env *env);
int				count_flags(t_totems *input, int sect);
void			print_vector(t_transformer *runner);
char			*getdollars(char *str, t_env *env);
int				expand_dollar(char **aux, t_env *env, char **ret);
t_transformer	*transform(t_totems *input, t_env *env);
void			ft_clear_transformer(t_transformer **runner, \
void (*del)(void *));
t_transformer	*init_transformer(t_transformer *runner);

//Pipes
void			ft_pipes(t_transformer **contents, \
t_env *env);
void			ft_while_pipes(t_transformer *content, t_tools *tools, \
t_env *env);
void			ft_final_pipe(t_transformer *content, t_tools *tools, \
t_env *env, int i);
void			ft_exit_process(int condition, char *argv);
void			ft_frst_child_pipe(t_transformer *smth, t_env *env, \
	t_tools *tools);
void			ft_mid_child_pipe(t_transformer *smth, t_env *env, \
	t_tools *tools, int i);
void			ft_bastard(t_transformer *smth, t_env *env, \
	t_tools *tools, int i);
int				count_cmds(t_transformer *data);
int				single_cmd(int npipes, t_transformer *smth, t_env *env);
void			single_cmd_2(int ofdin, int ofdout, t_transformer *smth, \
	t_env *env);
void			ft_execute(t_transformer *smth, t_env *env);
int				ft_check_directory(char **flags);
char			*ft_env_path(char **env, char *argv, char **flags);
char			**ft_path_split(char **env);
void			ft_print_error(char *error, char *arg);
void			ft_error(t_transformer *smth, int cond);
int				rederror(void);
void			here_doc(t_transformer *content, t_env *env);
void			while_heredoc(t_transformer *content, t_env *env, char *str, \
int quotes);
void			find_variable(char	*str, int fd, int *i, t_env *env);
void			exit_here(int code);
void			execute_heredoc(t_transformer *runner, t_env *env);
void			cutstr(char *str, char c);
void			allocate_fds(t_tools *tools);
void			close_all_fds(t_tools *tools);

//System functions
void			rl_replace_line(const char *text, int clear_undo);
#endif
