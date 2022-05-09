/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/09 16:44:01 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipes(t_transformer **contents, t_totems *input, t_env *env);
void	ft_while_pipes(t_transformer *content, t_tools *tools, t_env *env);
void	ft_final_pipe(t_transformer *content, t_tools *tools, t_env *env, \
		int i);
void	allocate_fds(t_tools *tools);
void	close_all_fds(t_tools *tools);

void	allocate_fds(t_tools *tools)
{
	int	i;

	i = 0;
	tools->fd = malloc(tools->npipes * sizeof(int *));
	while (i < tools->npipes)
	{
		tools->fd[i] = malloc(2 * sizeof(int));
		tools->fd[i][0] = -42;
		tools->fd[i][1] = -42;
		i++;
	}
}

void	close_all_fds(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->npipes)
	{
		close(tools->fd[i][0]);
		close(tools->fd[i][1]);
		i++;
	}
}
void	ft_pipes(t_transformer **contents, t_totems *input, t_env *env)
{
	int				i;
	t_transformer	*content;
	t_tools			*tools;

	g_util.ofdin = dup(STDIN_FILENO);
	g_util.ofdout = dup(STDOUT_FILENO);
	content = *contents;
	tools = malloc(sizeof(t_tools));
	tools->npipes = count_cmds(content) - 1;
	tools->pid = malloc((tools->npipes + 1) * sizeof(int));
	if (single_cmd(tools->npipes, content, env))
		return ;
	allocate_fds(tools);
	pipe(tools->fd[0]);
	tools->pid[0] = fork();
	if (tools->pid[0] == 0)
		ft_frst_child_pipe(content, env, tools);
	else
		ft_while_pipes(content, tools, env);
	i = -1;
	while (++i < (tools->npipes + 1))
	{
		wait(&(tools->pid[i]));
		if (WIFEXITED(tools->pid[i]))
			g_util.exit_value = WEXITSTATUS(tools->pid[i]);
		if (WIFSIGNALED(tools->pid[i]))
			g_util.exit_value = 130;
	}
}

void	ft_while_pipes(t_transformer *content, t_tools *tools, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	content = content->next;
	while (content && content->next)
	{
		pipe(tools->fd[j]);
		close(tools->fd[i][WRITE_END]);
		tools->pid[j] = fork();
		if (tools->pid[j] == 0)
			ft_mid_child_pipe(content, env, tools, i);
		close(tools->fd[i][READ_END]);
		i++;
		j++;
		content = content->next;
	}
	if (content)
		ft_final_pipe(content, tools, env, i);
}

void	ft_final_pipe(t_transformer *content, t_tools *tools, t_env *env, int i)
{
	close(tools->fd[i][WRITE_END]);
	tools->pid[i] = fork();
	if (tools->pid[i] == 0)
		ft_bastard(content, env, tools, i);
	close(tools->fd[i][READ_END]);
	close(content->fdout);
}
