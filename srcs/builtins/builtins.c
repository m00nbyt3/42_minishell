/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/28 12:59:42 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_builtins(t_transformer *runner, t_env *env);
int		select_cmd(t_transformer *runner, t_env *env, int ofdin, int ofdout);
void	shell_level(t_env *env);

int	ft_builtins(t_transformer *runner, t_env *env)
{
	int		ofdin;
	int		ofdout;

	if (!select_cmd(runner, env, ofdin, ofdout))
		return (0);
	return (1);
}

void	shell_level(t_env *env)
{
	int		i;
	int 	level;
	//char	*aux;

	i = 0;
	while (env->array[i])
	{
		if (ft_strncmp("SHLVL=", env->array[i], 5) == 0)
			level = ft_atoi(env->array[i] + 5);
		i++;
	}
	env->array[i] = ft_strdup(ft_strjoin("SHLVL", ft_itoa(level + 1)));
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
	else if (ft_strcmp(runner->cmd, "./minishell"))
		shell_level(env);
	else if (ft_strcmp(runner->cmd, "exit"))
		exit(0); //Add function to exit freeing all
	else
	{
		runner = orig;
		return (0);
	}
	runner = orig;
	return (1);
}
