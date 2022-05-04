/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/04 18:39:49 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);
void    ft_export(t_transformer *orunner, t_env *env);
char	**ft_export_add(t_transformer *runner, char **environ);

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
		tmp = ft_vsrch_var("USER", env);
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

int		add_to_env(t_transformer *orunner)
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

void    ft_export(t_transformer *orunner, t_env *env)
{
    t_totems            *input;
    t_transformer   	*runner;
    char           		 *sort;
	char **aux;
	int i = 0;
    if (orunner->flags[1])
	{
		if (add_to_env(orunner))
		{
    		aux = ft_export_add(orunner, env->array);
			env->array = aux;
			aux = ft_export_add(orunner, env->export);
			ft_free_matrix(env->export);
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
	int len;
	int i;
	int j;
	char **env;

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
