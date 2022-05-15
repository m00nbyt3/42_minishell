/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:09:46 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/15 16:14:59 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_transformer *orunner, t_env *env);
char	**ft_export_add(t_transformer *runner, char **environ);
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

int	variable_match(char *var, char *name)
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
	return (env);
}
//free(environ) in ft_env_add;

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
