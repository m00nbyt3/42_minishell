/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:09:46 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/17 16:35:33 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_export(t_transformer *orunner, t_env *env);
static void	ft_export_2(t_transformer *orunner, t_env *env, char *vname);
char		**ft_export_add(t_transformer *runner, char **environ);
char		*add_to_env(t_transformer *orunner);
char		**ft_env_add(char *toadd, char **environ);

void	ft_export(t_transformer *orunner, t_env *env)
{
	char	*vname;
	char	**aux;
	int		i;

	if (orunner->flags[1])
	{
		vname = add_to_env(orunner);
		if (vname)
			ft_export_2(orunner, env, vname);
		else
		{
			i = get_env_pos(orunner->flags[1], env->export);
			if (i != -1)
				replace_env(orunner->flags[1], env->array);
			else
			{
				aux = ft_export_add(orunner, env->export);
				free(env->export);
				env->export = aux;
			}
		}
	}
	else
		sort_mtx(env->export);
}

static void	ft_export_2(t_transformer *orunner, t_env *env, char *vname)
{
	char	**aux;
	int		i;

	i = get_env_pos(vname, env->array);
	if (i != -1)
		replace_env(orunner->flags[1], env->array);
	else
	{
		aux = ft_export_add(orunner, env->array);
		free(env->array);
		env->array = aux;
	}
	i = get_env_pos(vname, env->export);
	if (i != -1)
		replace_env(orunner->flags[1], env->export);
	else
	{
		aux = ft_export_add(orunner, env->export);
		free(env->export);
		env->export = aux;
	}
	free(vname);
}

char	**ft_export_add(t_transformer *runner, char **environ)
{
	int		len;
	int		i;
	int		j;
	char	**env;

	len = ft_mtxlen(environ) + 2;
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
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = ft_strdup(toadd);
	env[i + 1] = 0;
	ft_free_matrix(environ);
	return (env);
}

char	*add_to_env(t_transformer *orunner)
{
	int		i;
	char	*vname;

	i = 0;
	while (orunner->flags[1][i])
	{
		if (orunner->flags[1][i] == '=')
		{
			vname = malloc((i + 1) * sizeof(char));
			ft_strlcpy(vname, orunner->flags[1], (i + 1));
			return (vname);
		}
		i++;
	}
	return (0);
}
