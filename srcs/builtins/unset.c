/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:41:35 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/13 13:52:38 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_transformer *orunner, t_env *env);
char	**find_and_quit(char **env, char *var);
int		var_exist(char *str, char **environ, int i, int len);
char	**replace_env(char *toadd, char **environ);

void	ft_unset(t_transformer *orunner, t_env *env)
{
	char	**aux;
	char	*env_name;
	int		i;

	if (orunner->flags[1])
	{
		if (!var_exist(orunner->flags[1], env->array, -1, \
		ft_strlen(orunner->flags[1])))
		{
			aux = find_and_quit(env->array, orunner->flags[1]);
			env->array = aux;
		}
		if (!var_exist(orunner->flags[1], env->export, -1, \
		ft_strlen(orunner->flags[1])))
		{
			aux = find_and_quit(env->export, orunner->flags[1]);
			env->export = aux;
		}
	}
}

char	**find_and_quit(char **env, char *var_name)
{
	int		i;
	char	**copy;
	char	**aux;

	copy = ft_mtxdup(env);
	i = 0;
	while (copy[i])
	{
		if (!var_exist(var_name, env, i, ft_strlen(var_name)))
			break ;
		i++;
	}
	copy[i] = 0;
	aux = copy + (i + 1);
	copy = ft_mtxjoin(copy, aux);
	return (copy);
}

int	var_exist(char *str, char **environ, int i, int len)
{
	if (!len)
	{
		while (str[len] != '=' && str[len])
			len++;
	}
	else
		str = chr2str('=', str, 0);
	if (i != -1)
	{
		if (!ft_strncmp(environ[i], str, len))
			if (environ[i][len] == '=' || !environ[i][len])
				return (0);
		return (1);
	}
	else
	{
		i = 0;
		while (environ[i])
		{
			if (!ft_strncmp(environ[i], str, len))
				if (environ[i][len] == '=' || !environ[i][len])
					return (0);
			i++;
		}
		return (1);
	}
}

char	**replace_env(char *toadd, char **environ)
{
	char	*aux;
	int		i;

	i = 0;
	while (environ[i])
	{
		if (!var_exist(toadd, environ, i, 0))
			environ[i] = ft_strdup(toadd);
		i++;
	}
	return (environ);
}
