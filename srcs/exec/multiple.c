/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:02 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/23 11:35:19 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_transformer *data);
int	single_cmd(int npipes, t_transformer *smth, char **env);

void	ft_execute(t_transformer *smth, char **env)
{
	char	*command;

	if	(!*smth->cmd)
		ft_exit_process(1, smth->cmd);
	command = ft_env_path(env, smth->cmd, smth->flags);
	if (execve(command, smth->flags, env) < 0)
		ft_exit_process(2, smth->cmd);
	ft_free_matrix(smth->flags);
	exit(0);
}

void	ft_frst_child_pipe(t_transformer *smth, char **env, int *fd)
{
	close(fd[READ_END]);
	if (smth->fdin != 0)
	{
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
	if (smth->fdout != 1)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
	}
	ft_execute(smth, env);
}

void 	ft_mid_child_pipe(t_transformer *smth, char **env, int *fd1, int *fd2)
{
	dup2(fd1[READ_END], STDIN_FILENO);
	close(fd1[READ_END]);
	dup2(fd2[WRITE_END], STDOUT_FILENO);
	close(fd2[WRITE_END]);
	ft_execute(smth, env);
}

void	ft_bastard(t_transformer *smth, char **env, int *fd1)
{
	dup2(fd1[READ_END], STDIN_FILENO);
	close(fd1[READ_END]);
	
	if (smth->fdout != 1)
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	ft_execute(smth, env);
}

void	ft_pipes(t_transformer **smtha, char **env, t_totems *input, t_list *envlist)
{
	int	**fd;
	int	pid;
	t_transformer *smth;
	int	i;
	int	npipes;

	smth = *smtha;
	i = 0;
	npipes = count_cmds(smth) - 1;
	if (single_cmd(npipes, smth, env))
		return ;
	fd = malloc(npipes * sizeof(int *));
	*fd = malloc(2 * sizeof(int));
	pipe(*fd);
	pid = fork();
	if (pid == 0)
		ft_frst_child_pipe(smth, env, fd[0]);
	else
	{
		wait(&pid);
		if(!ft_builtins(input, &envlist) && smth->next)
		{
			smth = smth->next;
			while (smth && smth->next)
			{
				close(fd[i][WRITE_END]);
				fd[i + 1] = malloc(2 * sizeof(int));
				pipe(fd[i + 1]);
				pid = fork();
				if (pid == 0)
					ft_mid_child_pipe(smth, env, fd[i], fd[i + 1]);
				close(fd[i][READ_END]);
				wait(&pid);
				i++;
				smth = smth->next;
			}
			if (smth)
			{
				close(fd[i][WRITE_END]);
				pid = fork();
				if (pid == 0)
					ft_bastard(smth, env, fd[i]);
				close(fd[i][READ_END]);
				wait(&pid);
			}
		}
	}
}

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
	return(i);
}

int	single_cmd(int npipes, t_transformer *smth, char **env)
{
	int	pid;

	if (!npipes)
	{
		pid = fork();
		if (pid == 0)
		{
			if (smth->fdin != 0)
			{
				dup2(smth->fdin, STDIN_FILENO);
				close(smth->fdin);
			}
			if (smth->fdout != 1)
			{
				dup2(smth->fdout, STDOUT_FILENO);
				close(smth->fdout);
			}
			
				ft_execute(smth, env);
		}
		wait(&pid);
		return (1);
	}
	return (0);
}