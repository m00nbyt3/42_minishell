/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/15 17:45:18 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_builtins(t_transformer *runner, char **env);
int		select_cmd(t_transformer *runner, char **env, int ofdin, int ofdout);

int	ft_builtins(t_transformer *runner, char **env)
{
	int		ofdin;
	int		ofdout;

	ofdin = dup(STDIN_FILENO);
	ofdout = dup(STDOUT_FILENO);
	if (!select_cmd(runner, env, ofdin, ofdout))
		return (0);
	dup2(ofdin, STDIN_FILENO);
	close(ofdin);
	dup2(ofdout, STDOUT_FILENO);
	close(ofdout);
	return (1);
}

int	select_cmd(t_transformer *runner, char **env, int ofdin, int ofdout)
{
	void	*orig;

	orig = runner;
	if (ft_strcmp(runner->cmd, "env"))
		//ft_print_lst(*env);
		printf("env\n");
	else if (ft_strcmp(runner->cmd, "echo"))
		ft_echo(runner);
	else if (ft_strcmp(runner->cmd, "cd"))
		ft_cd(runner, env);
	else if (ft_strcmp(runner->cmd, "pwd"))
		ft_pwd();
	else if (ft_strcmp(runner->cmd, "exit"))
		exit(0); //Add function to exit freeing all
	else
	{
		runner = orig;
		dup2(ofdin, STDIN_FILENO);
		close(ofdin);
		dup2(ofdout, STDOUT_FILENO);
		close(ofdout);
		return (0);
	}
	runner = orig;
	return (1);
}
