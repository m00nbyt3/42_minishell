/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/10 11:54:43 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);

void	ft_echo(t_transformer *runner)
{
	void	*orig;
	int		newline;
	int		i;

	orig = runner;
	newline = 1;
	i = 1;
	if (*(runner->flags + i) == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strcmp(*(runner->flags + i), "-n"))
	{
			newline = 0;
			i++;
	}
	while (*(runner->flags + i))
	{
		if (*(runner->flags + i + 1))
		{
			ft_putstr_fd(*(runner->flags + i), 1);
			write(1, " ", 1);
		}
		else
			ft_putstr_fd(*(runner->flags + i), 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	runner = orig;
}

void	ft_cd(t_transformer *runner, char **env)
{
	char	*tmp;
	char	*home;

	if (*(runner->flags + 1))
		chdir(*(runner->flags + 1));
	else
	{
		tmp = 0;
		tmp = ft_vsrch_var("USER", env);
		if (!tmp)
		{
			write(2, "W4V3shell: cd: HOME not set\n", 28);
			g_util.exit_value = 2;
			return ;
		}
		home = ft_strjoin("/Users/", tmp);
		free(tmp);
		chdir(home);
	}
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 0);
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
}
