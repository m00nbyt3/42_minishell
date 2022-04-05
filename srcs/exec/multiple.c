/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:02 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/05 15:10:37 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipes(t_transformer **contents, char **env, t_totems *input, \
		t_list *envlist);
void	ft_while_pipes(t_transformer *content, t_tools *tools, char **env);
void	ft_final_pipe(t_transformer *content, t_tools *tools, char **env, int i);

void	ft_pipes(t_transformer **contents, char **env, t_totems *input, \
		t_list *envlist)
{
	int				i;
	t_transformer	*content;
	t_tools			*tools;

	content = *contents;
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
		ft_while_pipes(content, tools, env);
	i = -1;
	while (++i < (tools->npipes + 1))
		wait(&(tools->pid[i]));
}

void	ft_while_pipes(t_transformer *content, t_tools *tools, char **env)
{
	int	i;

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
		i++;
		content = content->next;
	}
	if (content)
		ft_final_pipe(content, tools, env, i);
}

void	ft_final_pipe(t_transformer *content, t_tools *tools, char **env, int i)
{
	close(tools->fd[i][WRITE_END]);
	tools->pid[i] = fork();
	if (tools->pid[i] == 0)
		ft_bastard(content, env, tools->fd[i]);
	close(tools->fd[i][READ_END]);
}
