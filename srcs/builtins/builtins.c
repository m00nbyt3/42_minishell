/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/11 16:24:24 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_builtins(t_transformer *runner, t_env *env);
int		select_cmd(t_transformer *runner, t_env *env, int ofdin, int ofdout);

int	ft_builtins(t_transformer *runner, t_env *env)
{
	int		ofdin;
	int		ofdout;

	if (!select_cmd(runner, env, ofdin, ofdout))
		return (0);
	return (1);
}

int	select_cmd(t_transformer *runner, t_env *env, int ofdin, int ofdout)
{
	void	*orig;

	orig = runner;
	if (ft_strcmp(runner->cmd, "env"))
		ft_print_mtx(env->array);
	else if (ft_strcmp(runner->cmd, "echo"))
		ft_echo(runner);
	else if (ft_strcmp(runner->cmd, "cd"))
		ft_cd(runner, env->array);
	else if (ft_strcmp(runner->cmd, "pwd"))
		ft_pwd();
	else if (ft_strcmp(runner->cmd, "export"))
		ft_export(runner, env);
	else if (ft_strcmp(runner->cmd, "unset"))
		ft_unset(runner, env);
	else if (ft_strcmp(runner->cmd, "exit"))
		ft_builtin_exit(runner);
	else
	{
		runner = orig;
		return (0);
	}
	runner = orig;
	return (1);
}
