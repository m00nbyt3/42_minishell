/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:41:35 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/16 16:31:29 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_transformer *orunner, t_env *env);
char	**find_and_quit(char **env, char *var);
int		var_exist(char *str, char **environ, int i, int len);
char	**replace_env(char *toadd, char **environ);
int		ret_free(int val, char *str, char *orig);

void	ft_unset(t_transformer *orunner, t_env *env)
{
	char	**aux;

	aux = 0;
	if (orunner->flags[1])
	{
		if (!var_exist(orunner->flags[1], env->array, -1, \
		ft_strlen(orunner->flags[1])))
		{
			aux = find_and_quit(env->array, orunner->flags[1]);
			ft_free_matrix(env->array);
			env->array = aux;
		}
		if (!var_exist(orunner->flags[1], env->export, -1, \
		ft_strlen(orunner->flags[1])))
		{
			aux = find_and_quit(env->export, orunner->flags[1]);
			ft_free_matrix(env->export);
			env->export = aux;
		}
	}
}

char	**find_and_quit(char **env, char *var_name)
{
	int		i;
	char	**copy;
	char	**aux;
	char	**new;

	copy = ft_mtxdup(env);
	i = 0;
	while (copy[i])
	{
		if (!var_exist(var_name, env, i, ft_strlen(var_name)))
			break ;
		i++;
	}
	free(copy[i]);
	copy[i] = 0;
	aux = copy + (i + 1);
	new = ft_mtxjoin(copy, aux);
	ft_free_mtxbasic(aux);
	ft_free_matrix(copy);
	return (new);
}

int	var_exist(char *str, char **environ, int i, int len)
{
	char	*orig;

	orig = str;
	if (!len)
		while (str[len] != '=' && str[len])
			len++;
	else
		str = chr2str('=', str, 0);
	if (i != -1)
	{
		if (!ft_strncmp(environ[i], str, len))
			if (environ[i][len] == '=' || !environ[i][len])
				return (ret_free(0, str, orig));
		return (ret_free(1, str, orig));
	}
	else
	{
		i = 0;
		while (environ[i])
		{
			if (!ft_strncmp(environ[i], str, len))
				if (environ[i][len] == '=' || !environ[i][len])
					return (ret_free(0, str, orig));
			i++;
		}
		return (ret_free(1, str, orig));
	}
}

int	ret_free(int val, char *str, char *orig)
{
	if (str != orig)
		free(str);
	return(val);
}

char	**replace_env(char *toadd, char **environ)
{
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
