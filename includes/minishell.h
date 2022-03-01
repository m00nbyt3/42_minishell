/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:43:29 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/01 17:33:51 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ_END 0
# define WRITE_END 1
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

typedef struct	s_totem
{
	char	*input;
	char	**flags;
	int		fd;
	int		type;
}				t_totem;
t_list *store_env_in_list(char **environ);
void	ft_builtins(char *input, t_list **env);
void	ft_env(t_list **env);
void	ft_chk_quotes(t_list *args);
#endif

