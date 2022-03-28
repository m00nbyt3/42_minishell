/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:02 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/28 17:37:35 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_transformer *data);
int	single_cmd(int npipes, t_transformer *smth, char **env);

void	ft_execute(t_transformer *smth, char **env)
{
	char	*command;

	if (!*smth->cmd)
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
	if (smth->fdin != -2)
	{
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
	if (smth->fdout == -2)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
	}
	else
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	ft_execute(smth, env);
}

void	ft_mid_child_pipe(t_transformer *smth, char **env, int *fd1, int *fd2)
{
	if (smth->fdin == -2)
	{
		dup2(fd1[READ_END], STDIN_FILENO);
		close(fd1[READ_END]);
	}
	else
	{
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
	if (smth->fdout == -2)
	{
		dup2(fd2[WRITE_END], STDOUT_FILENO);
		close(fd2[WRITE_END]);
	}
	else
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	ft_execute(smth, env);
}

void	ft_bastard(t_transformer *smth, char **env, int *fd1)
{
	if (smth->fdin == -2)
	{
		dup2(fd1[READ_END], STDIN_FILENO);
		close(fd1[READ_END]);
	}
	else
	{
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
	if (smth->fdout != -2)
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	ft_execute(smth, env);
}

void	ft_final_pipe(t_transformer *content, t_tools *tools, char **env, int i)
{
	close(tools->fd[i][WRITE_END]);
	tools->pid[i] = fork();
	if (tools->pid[i] == 0)
		ft_bastard(content, env, tools->fd[i]);
	close(tools->fd[i][READ_END]);
	//wait(&(tools->pid[i]));
}

void	ft_while_pipes(t_transformer *content, t_tools *tools, char **env)
{
	int i;

	i = 0;
	content = content->next;
	while (content && content->next)
	{
		close(tools->fd[i][WRITE_END]);
		tools->fd[i + 1] = malloc(2 * sizeof(int));
		pipe(tools->fd[i + 1]);
		tools->pid[i] = fork();
		if (tools->pid[i] == 0)
			ft_mid_child_pipe(content, env, tools->fd[i], tools->fd[i + 1]);
		close(tools->fd[i][READ_END]);
		//wait(&(tools->pid[i]));
		i++;
		content = content->next;
	}
	if (content)
		ft_final_pipe(content, tools, env, i);
}

void	ft_pipes(t_transformer **contents, char **env, t_totems *input, \
		t_list *envlist)
{
	int i;

	t_transformer	*content;
	t_tools			*tools;

	content = *contents;
	printf("%s\n", content->cmd);
	tools = malloc(sizeof(t_tools));
	tools->npipes = count_cmds(content) - 1;
	tools->pid = malloc((tools->npipes + 1) * sizeof(int));
	if (single_cmd(tools->npipes, content, env))
		return ;
	tools->fd = malloc(tools->npipes * sizeof(int *));
	tools->fd[0] = malloc(2 * sizeof(int));
	pipe(tools->fd[0]);
	tools->pid[0] = fork();
	if (tools->pid[0] == 0)
		ft_frst_child_pipe(content, env, tools->fd[0]);
	else
	{
		//wait(&(tools->pid[0]));
		if (!ft_builtins(input, &envlist) && content->next)
			ft_while_pipes(content, tools, env);
	}
	i = -1;
	while (++i < (tools->npipes + 1))
		wait(&(tools->pid[i]));
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
	printf("%d\n", i);
	return (i);
}

int	single_cmd(int npipes, t_transformer *smth, char **env)
{
	int	pid;

	if (!npipes)
	{
		pid = fork();
		if (pid == 0)
		{
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
			ft_execute(smth, env);
		}
		wait(&pid);
		return (1);
	}
	return (0);
}
