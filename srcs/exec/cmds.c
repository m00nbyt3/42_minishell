/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:53:51 by ycarro            #+#    #+#             */
/*   Updated: 2022/04/19 10:37:43 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_cmds(t_transformer *data);
int		single_cmd(int npipes, t_transformer *smth, char **env);
void	ft_execute(t_transformer *smth, char **env);

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

int	single_cmd(int npipes, t_transformer *smth, char **env)
{
	int	pid;

	if (!npipes)
	{
		if (ft_builtins(smth, env))
			return (1);
		pid = fork();
		if (pid == 0)
		{
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
			ft_execute(smth, env);
		}
		sigignore(SIGINT);
		wait(&pid);
		return (1);
	}
	return (0);
}

void	ft_execute(t_transformer *smth, char **env)
{
	char	*command;

	if (smth->heredoc)
		here_doc(smth);
	command = ft_env_path(env, smth->cmd, smth->flags);
	if (execve(command, smth->flags, env) < 0)
		ft_error(smth, 1);
	ft_free_matrix(smth->flags);
	exit(0);
}
