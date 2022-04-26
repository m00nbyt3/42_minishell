/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:53:51 by ycarro            #+#    #+#             */
/*   Updated: 2022/04/26 16:14:30 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_cmds(t_transformer *data);
int		single_cmd(int npipes, t_transformer *smth,  t_env *env);
void	ft_execute(t_transformer *smth,  t_env *env);

int	count_cmds(t_transformer *data)
{
	void	*orig;
	int		ret;
	int		i;

	orig = data;
	i = 0;
	while (data)
	{
		i++;
		data = data->next;
	}
	data = orig;
	return (i);
}

int	single_cmd(int npipes, t_transformer *smth,  t_env *env)
{
	int	pid;
	int	ofdin;
	int	ofdout;

	if (!npipes)
	{
		ofdin = dup(STDIN_FILENO);
		ofdout = dup(STDOUT_FILENO);

		//------------------------
		if (!*smth->cmd)
			ft_error(smth, 1);
		if (smth->fdin != -2)
		{
			dup2(smth->fdin, STDIN_FILENO);
			close(smth->fdin);
		}
		if (smth->fdout != -2)
		{
			dup2(smth->fdout, STDOUT_FILENO);
			close(smth->fdout);
		}
		if (smth->fdin == -1 || smth->fdout == -1)
			ft_error(smth, 0);
		//-----------------------------

		//-----------------------------
		if (ft_builtins(smth, env))
		{
			dup2(ofdin, STDIN_FILENO);
			close(ofdin);
			dup2(ofdout, STDOUT_FILENO);
			close(ofdout);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				ft_execute(smth, env);
			}
		}
		//-----------------------------
		sigignore(SIGINT);
		wait(&pid);
		return (1);
	}
	return (0);
}

void	ft_execute(t_transformer *smth,  t_env *env)
{
	char	*command;

	if (smth->heredoc)
		here_doc(smth);
	if (ft_builtins(smth, env))
		;
	else
	{
		command = ft_env_path(env->array, smth->cmd, smth->flags);
		if (execve(command, smth->flags, env->array) < 0)
			ft_error(smth, 1);
	}
	ft_free_matrix(smth->flags);
	exit(0);
}
