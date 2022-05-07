/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:09:46 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/07 15:40:56 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_transformer *orunner, t_env *env);
int		var_exist(t_transformer *runner, char **environ);
char	**replace_env(t_transformer *runner, char **environ);
char	**ft_export_add(t_transformer *runner, char **environ);
void	ft_unset(t_transformer *orunner, t_env *env);
char	**find_and_quit(char **env, char *var);
int		variable_match(char *var, char *name);
int		add_to_env(t_transformer *orunner);

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

int	var_exist(t_transformer *runner, char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (variable_match(environ[i], runner->flags[1]))
			return (1);
		i++;
	}
	return (0);
}

char	**replace_env(t_transformer *runner, char **environ)
{
	char	*aux;
	int		i;

	i = 0;
	while (environ[i])
	{
		if (variable_match(environ[i], runner->flags[1]))
			environ[i] = ft_strdup(runner->flags[1]);
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

	if (var_exist(runner, environ))
		return (replace_env(runner, environ));
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

void	ft_unset(t_transformer *orunner, t_env *env)
{
	char	**aux;
	char	*env_name;
	int		i;

	if (orunner->flags[1])
	{
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
		if (variable_match(copy[i], var_name))
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
