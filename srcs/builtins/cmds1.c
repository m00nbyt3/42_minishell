/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:31:48 by ycarro            #+#    #+#             */
/*   Updated: 2022/04/21 10:56:01 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);
void    ft_export(t_transformer *orunner, char **environ);
void	ft_export_add(t_transformer *runner, char **environ);

void	ft_echo(t_transformer *runner)
{
	void	*orig;
	int		newline;
	int		i;

	orig = runner;
	newline = 1;
	i = 1;
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

void    ft_export(t_transformer *orunner, char **environ)
{
    t_totems            *input;
    t_transformer   	*runner;
    char           		 *sort;

    if (orunner->flags[1])
    	ft_export_add(orunner, environ);
	else
	{

		printf("here");
		sort = "env | sort";
    	input = sp_split(sort);
    	runner = transform(input);
 		if (input)
		{
			ft_pipes(&runner, environ, input, 0);
			ft_clear_input(&input, free);
		}
    	ft_clear_transformer(&runner, free);
	}
}

int	ft_mtxlen(char **mtx)
{
	int i;

	i = 0;
	while(mtx[i])
		i++;
	return (i);
}

void	ft_export_add(t_transformer *runner, char **environ)
{
	int len;
	int i;
	int j;
	char **env;

	env = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (environ[i])
	{
		env[i] = environ[i];
		dprintf(2, "env[%i]: %s\n", i, env[i]);
		i++;
	}
	j = 0;
	while (runner->flags[j])
	{
		env[i] = ft_strdup(runner->flags[j]);
		i++ && j++;
	}
	env[i] = 0;
	i = 0;
	/*while (environ[i])
	{
		free(environ[i]);
		i++;
	}*/
	//free(environ);
	environ = env;
}
