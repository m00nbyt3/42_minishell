/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:53:51 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/05 14:37:57 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_cmds(t_transformer *data);
int		single_cmd(int npipes, t_transformer *smth,  t_env *env);
void	single_cmd_2(int ofdin, int	ofdout, t_transformer *smth,  t_env *env);
void	ft_execute(t_transformer *smth,  t_env *env);
void	redirection(t_transformer *smth, t_env *env);
void	set_origina_fd(void);

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

void	redirection(t_transformer *smth, t_env *env)
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
}

void	set_origina_fd(void)
{
	int	ofdin;
	int	ofdout;

	if (!npipes)
	{
		ofdin = dup(STDIN_FILENO);
		ofdout = dup(STDOUT_FILENO);
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
		single_cmd_2(ofdin, ofdout, smth, env);
		return (1);
	}
	return (0);
}

void	single_cmd_2(int ofdin, int	ofdout, t_transformer *smth,  t_env *env)
{
	int	pid;

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
			ft_execute(smth, env);
	}
	sigignore(SIGINT);
	wait(&pid);
	dup2(ofdin, STDIN_FILENO);
	close(ofdin);
	dup2(ofdout, STDOUT_FILENO);
	close(ofdout);
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
		if (command == 0)
		{
			write(2, "W4V3shell: ", 11);
			ft_putstr_fd(smth->cmd, 2);
			write(2, " :command not found\n", 20);
			exit (1);
		}
		if (execve(command, smth->flags, env->array) < 0)
		{
			write(2, "W4V3shell: ", 11);
			ft_putstr_fd(smth->cmd, 2);
			perror(" ");
			exit (1);
		}
	}
	ft_free_matrix(smth->flags);
	exit(0);
}
