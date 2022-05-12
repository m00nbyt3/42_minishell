/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:09:46 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/12 11:29:09 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_transformer *orunner, t_env *env);
int		var_exist(char *str, char **environ, int i, int len);
char	**replace_env(char *toadd, char **environ);
char	**ft_export_add(t_transformer *runner, char **environ);
void	ft_unset(t_transformer *orunner, t_env *env);
char	**find_and_quit(char **env, char *var);
int		variable_match(char *var, char *name);
int		add_to_env(t_transformer *orunner);
char	**ft_env_add(char *toadd, char **environ);

void	ft_export(t_transformer *orunner, t_env *env)
{
	char				**aux;

	if (orunner->flags[1])
	{
		if (add_to_env(orunner))
		{
			aux = ft_export_add(orunner, env->array);
			env->array = aux;
			aux = ft_export_add(orunner, env->export);
			env->export = aux;
		}
		else
			env->export = ft_export_add(orunner, env->export);
	}
	else
		sort_mtx(env->export);
}

int		variable_match(char *var, char *name)
{
	int	i;

	i = 0;
	while (var[i] && name[i] && var[i] != '=' && name[i] != '=')
	{
		if (var[i] != name[i])
			return (0);
		i++;
	}
	return (1);
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
		return(ft_strncmp(environ[i], str, len + 1));
	else
	{
		i = 0;
		while (environ[i])
		{
			if (!ft_strncmp(environ[i], str, len + 1))
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

char	**ft_export_add(t_transformer *runner, char **environ)
{
	int		len;
	int		i;
	int		j;
	char	**env;

	if (!var_exist(runner->flags[1], environ, -1, 0))
		return (replace_env(runner->flags[1], environ));
	len = ft_mtxlen(runner->flags) + ft_mtxlen(environ);
	env = malloc((len) * sizeof(char *));
	i = 0;
	while (environ[i])
	{
		env[i] = environ[i];
		i++;
	}
	j = 1;
	while (runner->flags[j])
	{
		env[i] = ft_strdup(runner->flags[j]);
		i++;
		j++;
	}
	env[i] = 0;
	return (env);
}

char	**ft_env_add(char *toadd, char **environ)
{
	int		len;
	int		i;
	int		j;
	char	**env;

	len = 2 + ft_mtxlen(environ);
	env = malloc((len) * sizeof(char *));
	i = 0;
	while (environ[i])
	{
		env[i] = environ[i];
		i++;
	}
	env[i] = ft_strdup(toadd);
	env[i + 1] = 0;
	//free(environ);
	return (env);
}

void	ft_unset(t_transformer *orunner, t_env *env)
{
	char	**aux;
	char	*env_name;
	int		i;

	if (orunner->flags[1])
	{
		if (var_exist(orunner->flags[1], env->array, -1, ft_strlen(orunner->flags[1])))
			return ;
		aux = find_and_quit(env->array, orunner->flags[1]);
		env->array = aux;
		aux = find_and_quit(env->export, orunner->flags[1]);
		env->export = aux;
	}
}

char	**find_and_quit(char **env, char *var_name)
{
	int		i;
	char	**copy;
	char	**aux;

	copy =  ft_mtxdup(env);
	i = 0;
	while (copy[i])
	{
		if (!var_exist(var_name, env, i, ft_strlen(var_name)))
			break ;
		i++;
	}
	copy[i] = 0;
	aux = copy + (i + 1);
	copy = ft_mtxjoin(copy,  aux);
	return (copy);
}
int	add_to_env(t_transformer *orunner)
{
	int	i;

	i = 0;
	while (orunner->flags[1][i])
	{
		if (orunner->flags[1][i] == '=')
			return (1);
		i++;
	}
	return (0);
}
