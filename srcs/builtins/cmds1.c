/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/06 09:26:09 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);
void	ft_export(t_transformer *orunner, t_env *env);
char	**ft_export_add(t_transformer *runner, char **environ);
void	ft_unset(t_transformer *orunner, t_env *env);
char	**find_and_quit(char **env, char *var);

void	ft_echo(t_transformer *runner)
{
	void	*orig;
	int		newline;
	int		i;

	orig = runner;
	newline = 1;
	i = 1;
	if (*(runner->flags + i) == 0)
		return ;
	if (ft_strcmp(*(runner->flags + i), "-n"))
	{
			newline = 0;
			i++;
	}
	while (*(runner->flags + i))
	{
		if (*(runner->flags + i + 1))
			printf("%s ", *(runner->flags + i));
		else
			printf("%s", *(runner->flags + i));
		i++;
	}
	if (newline)
		printf("\n");
	runner = orig;
}

void	ft_cd(t_transformer *runner, char **env)
{
	char	*tmp;
	char	*home;

	if (*(runner->flags + 1))
		chdir(*(runner->flags + 1));
	else
	{
		tmp = 0;
		tmp = ft_vsrch_var("USER", env);
		if (!tmp)
		{
			write(2, "W4V3shell: cd: HOME not set\n", 28);
			return ;
		}
		home = ft_strjoin("/Users/", tmp);
		free(tmp);
		printf("%s\n", home);
		chdir(home);
	}
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 0);
	printf("%s\n", buf);
	free(buf);
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

char	**ft_export_add(t_transformer *runner, char **environ)
{
	int		len;
	int		i;
	int		j;
	char	**env;

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

int		variable_match(char *var, char *name)
{
	int	i;

	i = 0;
	while (var[i] && name[i] && var[i] != '=')
	{
		if (var[i] != name[i])
			return (0);
		i++;
	}
	return (1);
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
	/*for (int j = 0; aux[j]; j++)
		dprintf(2, "----%s---\n", aux[j]);
	dprintf(2, "HOLAA\n");*/
	copy = ft_mtxjoin(copy,  aux);
	return (copy);
}
