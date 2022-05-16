/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/16 17:01:43 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_exit(t_transformer *runner, t_env *env);
void	flag_is_not_num(t_transformer *runner);
void	free_env(t_env *env);

void	ft_builtin_exit(t_transformer *runner, t_env *env)
{
	if (runner->flags[1])
	{
		if (!ft_is_str_num(runner->flags[1]))
			flag_is_not_num(runner);
		else if (runner->flags[2])
		{
			write(2, "exit\nW4V3shell: exit: too many arguments\n", 41);
			g_util->exit_value = 1;
			return ;
		}
		else
		{
			g_util->exit_value = ft_atoi(runner->flags[1]);
			exit(ft_atoi(runner->flags[1]));
		}
	}
	else
	{
		g_util->exit_value = 0;
		free_env(env);
		exit (0);
	}
}

void	flag_is_not_num(t_transformer *runner)
{
	write(2, "W4V3shell: exit: ", 17);
	ft_putstr_fd(runner->flags[1], 2);
	write(2, " : numeric argument required\n", 29);
	g_util->exit_value = 255;
	exit (255);
}

void	free_env(t_env *env)
{
	ft_free_matrix(env->array);
	ft_free_matrix(env->export);
	free(env);
	env = 0;
}
