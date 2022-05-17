/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:59:45 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/17 10:48:11 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);
void	mod_env_pwd(char **env);
void	file_not_found(char *path);
char	*go_to_last_path(char *path, char **env);

void	file_not_found(char *path)
{
	write(2, "W4V3shell: cd: ", 15);
	ft_putstr_fd(path, 2);
	write(2, " : No such file or directory\n", 30);
	g_util->exit_value = 1;
	free(path);
}

char	*go_to_last_path(char *path, char **env)
{
	free(path);
	path = get_my_env("OLDPWD", env);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	return (path);
}

void	ft_cd(t_transformer *runner, char **env)
{
	char	*path;

	if (*(runner->flags + 1))
		path = ft_strdup(*(runner->flags + 1));
	else
	{
		path = 0;
		path = get_my_env("HOME", env);
		if (!path)
		{
			write(2, "W4V3shell: cd: HOME not set\n", 28);
			g_util->exit_value = 1;
			return ;
		}
	}
	if (ft_strcmp(path, "-"))
		path = go_to_last_path(path, env);
	if (chdir(path) == -1)
	{
		file_not_found(path);
		return ;
	}
	mod_env_pwd(env);
	g_util->exit_value = 0;
	free(path);
}

void	mod_env_pwd(char **env)
{
	char	*toadd1;
	char	*toadd2;
	char	*path;

	path = get_my_env("PWD", env);
	toadd1 = ft_strjoin("OLDPWD=", path);
	free(path);
	path = getcwd(0, 0);
	toadd2 = ft_strjoin("PWD=", path);
	free(path);
	if (!var_exist("OLDPWD=", env, -1, 0))
		replace_env(toadd1, env);
	else
		ft_env_add(toadd1, env);
	if (!var_exist("PWD=", env, -1, 0))
		replace_env(toadd2, env);
	else
		ft_env_add(toadd2, env);
	free(toadd1);
	free(toadd2);
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 0);
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
	g_util->exit_value = 0;
}
