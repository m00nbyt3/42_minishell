/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/05 15:00:23 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_builtins(t_transformer *runner, t_list **env);
void	select_cmd(t_transformer *runner, t_list **env, int ofdin, int ofdout);

int	ft_builtins(t_transformer *runner, t_list **env)
{
	int		ofdin;
	int		ofdout;

	ofdin = dup(STDIN_FILENO);
	ofdout = dup(STDOUT_FILENO);
	select_cmd(runner, env, ofdin, ofdout);
	dup2(ofdin, STDIN_FILENO);
	close(ofdin);
	dup2(ofdout, STDOUT_FILENO);
	close(ofdout);
	return (1);
}

void	select_cmd(t_transformer *runner, t_list **env, int ofdin, int ofdout)
{
	void	*orig;

	orig = runner;
	if (ft_strcmp(runner->cmd, "env"))
		ft_print_lst(*env);
	if (ft_strcmp(runner->cmd, "echo"))
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
		return ;
	}
	runner = orig;
}
