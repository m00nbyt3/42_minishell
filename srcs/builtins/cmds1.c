/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/07 17:23:44 by agallipo         ###   ########.fr       */
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
			g_util.exit_value = 2;
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
