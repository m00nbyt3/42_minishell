/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:23:04 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/13 21:04:38 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_my_env(char *name, char **env);
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
			expanded = ft_strdup(env[i] + (len + 1));
			break ;
		}
		i++;
	}
	return (expanded);
}

t_env	*basic_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->array = ft_calloc(4, sizeof(char *));
	env->array[0] = ft_strdup(ft_strjoin("PWD=", getcwd(0, 0)));
	shell_level(env->array);
	env->array[2] = ft_strdup("_=/usr/bin/env");
	env->array[3] = 0;
	env->export = ft_mtxdup(env->array);
	env->list = store_env_in_list(env->array);
	return (env);
}

char	**shell_level(char **env)
{
	int		i;
	int		lvl;
	char	*aux;
	int		found;

	i = 0;
	lvl = 1;
	found = 0;
	while (env[i])
	{
		if (ft_strncmp("SHLVL=", env[i], 6) == 0)
		{
			found++;
			aux = env[i] + 6;
			lvl = ft_atoi(aux) + 1;
			if (lvl <= 0)
				lvl = 1;
			break ;
		}
		i++;
	}
	env[i] = ft_strdup(ft_strjoin("SHLVL=", ft_itoa(lvl)));
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
	env->list = store_env_in_list(environ);
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
