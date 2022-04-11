/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:31:48 by ycarro            #+#    #+#             */
/*   Updated: 2022/04/06 15:05:46 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
void	ft_cd(t_transformer *runner, char **env);
void	ft_pwd(void);

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
