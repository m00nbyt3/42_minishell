/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/11 17:23:30 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);
int		echo_comp_n(char *str);
void	ft_builtin_exit(t_transformer *runner);

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
	if (echo_comp_n(*(runner->flags + i)))
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

int	echo_comp_n(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return(1);
}

void	ft_cd(t_transformer *runner, char **env)
{
	char	*home;

	if (*(runner->flags + 1))
		chdir(*(runner->flags + 1));
	else
	{
		home = 0;
		home = ft_vsrch_var("HOME=", env);
		if (!home)
		{
			write(2, "W4V3shell: cd: HOME not set\n", 28);
			g_util.exit_value = 2;
			return ;
		}
		if (chdir(home) == -1)
		{
			write(2, "W4V3shell: cd: ", 15);
			ft_putstr_fd(home, 2);
			write(2, " : No such file or directory\n", 30);
			g_util.exit_value = 1;
		}
		free(home);
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

void	ft_builtin_exit(t_transformer *runner)
{
	if (runner->flags[1])
	{
		if (!ft_is_str_num(runner->flags[1]))
		{
			write(2, "W4V3shell: exit: ", 17);
			ft_putstr_fd(runner->flags[1], 2);
			write(2, " : numeric argument required\n", 29);
			g_util.exit_value = 255;
			exit (255);
		}
		else if (runner->flags[2])
		{
			write(2, "exit\nW4V3shell: exit: too many arguments\n", 41);
			g_util.exit_value = 1;
			return ;
		}
		else
		{
			g_util.exit_value = ft_atoi(runner->flags[1]);
			exit(ft_atoi(runner->flags[1]));
		}
	}
	else
		exit (0);
}
