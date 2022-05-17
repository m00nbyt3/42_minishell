/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:23:04 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/17 13:06:00 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_my_env(char *name, char **env);
int		get_env_pos(char *name, char **env);
t_env	*basic_env(void);
char	**shell_level(char **env);
t_env	*store_environ(void);
t_list	*store_env_in_list(char **environ);

char	*get_my_env(char *name, char **env)
{
	int		i;
	int		len;
	char	*expanded;

	len = ft_strlen(name);
	i = 0;
	expanded = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0)
		{
			if (*(env[i] + (len)) == '=')
			{
				expanded = ft_strdup(env[i] + (len + 1));
				break ;
			}
		}
		i++;
	}
	return (expanded);
}

int	get_env_pos(char *name, char **env)
{
	int		i;
	int		len;

	if(!name)
		return (-2);		
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0)
		{
			if (*(env[i] + (len)) == '=' || *(env[i] + (len)) == 0)
			{
				return(i);
				break ;
			}
		}
		i++;
	}
	return (-1);
}

t_env	*basic_env(void)
{
	t_env	*env;
	char	*path;

	env = malloc(sizeof(t_env));
	env->array = ft_calloc(4, sizeof(char *));
	path = getcwd(0, 0);
	env->array[0] = ft_strjoin("PWD=", path);
	free(path);
	shell_level(env->array);
	env->array[2] = ft_strdup("_=/usr/bin/env");
	env->array[3] = 0;
	env->export = ft_mtxdup(env->array);
	return (env);
}

char	**shell_level(char **env)
{
	int		i;
	int		lvl;
	char	*aux;
	char	*number;

	i = 0;
	lvl = 1;
	while (env[i])
	{
		if (ft_strncmp("SHLVL=", env[i], 6) == 0)
		{
			aux = env[i] + 6;
			lvl = ft_atoi(aux) + 1;
			if (lvl <= 0)
				lvl = 1;
			break ;
		}
		i++;
	}
	free(env[i]);
	number = ft_itoa(lvl);
	env[i] = ft_strjoin("SHLVL=", number);
	free(number);
	return (env);
}

t_env	*store_environ(void)
{
	t_env			*env;
	extern char		**environ;

	if (!(*environ))
		return (basic_env());
	env = malloc(sizeof(t_env));
	env->export = ft_mtxdup(environ);
	env->array = ft_mtxdup(environ);
	env->array = shell_level(env->array);
	return (env);
}

t_list	*store_env_in_list(char **environ)
{
	t_list	*env;

	env = NULL;
	while (*environ)
	{
		ft_lstadd_back(&env, ft_lstnew(*environ));
		environ++;
	}
	return (env);
}
