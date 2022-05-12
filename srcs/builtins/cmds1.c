/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/12 11:35:49 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);
int		echo_comp_n(char *str);
void	ft_builtin_exit(t_transformer *runner);
void	mod_env_pwd(char **env);

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
	g_util.exit_value = 0;
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
	char	*path;

	if (*(runner->flags + 1))
		path = *(runner->flags + 1);
	else
	{
		path = 0;
		path = ft_vsrch_var("HOME=", env);
		if (!path)
		{
			write(2, "W4V3shell: cd: HOME not set\n", 28);
			g_util.exit_value = 2;
			return ;
		}
	}
	if (chdir(path) == -1)
	{
		write(2, "W4V3shell: cd: ", 15);
		ft_putstr_fd(path, 2);
		write(2, " : No such file or directory\n", 30);
		g_util.exit_value = 1;
	}
	//free(path);
	mod_env_pwd(env);
	g_util.exit_value = 0;
}

void	mod_env_pwd(char **env)
{
	char *toadd1;
	char *toadd2;

	toadd1 = ft_strjoin("OLDPWD=", g_util.pwd);
	g_util.pwd = getcwd(0, 0);
	toadd2 = ft_strjoin("PWD=", g_util.pwd);
	if (!var_exist("OLDPWD=", env, -1, 0))
			replace_env(toadd1, env);
		else
			ft_env_add(toadd1, env);
	if (!var_exist("PWD=", env, -1, 0))
			replace_env(toadd2, env);
		else
			ft_env_add(toadd2, env);
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 0);
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
	g_util.exit_value = 0;
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
	{
		g_util.exit_value = 0;
		exit (0);
	}
}
