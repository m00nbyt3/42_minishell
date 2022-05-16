/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:52:39 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/16 12:48:07 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_frst_child_pipe(t_transformer *smth, t_env *env, t_tools *tools);
void	ft_mid_child_pipe(t_transformer *smth, t_env *env, t_tools *tools, \
int i);
void	mid_has_fdin_redirection(t_transformer *smth, t_tools *tools, int i);
void	ft_bastard(t_transformer *smth, t_env *env, t_tools *tools, int i);

void	ft_frst_child_pipe(t_transformer *smth, t_env *env, t_tools *tools)
{
	close(tools->fd[0][READ_END]);
	if (smth->fdin != -2)
	{
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
	if (smth->fdout == -2)
		dup2(tools->fd[0][WRITE_END], STDOUT_FILENO);
	else
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	close(tools->fd[0][WRITE_END]);
	if (smth->fdin == -1 || smth->fdout == -1)
		exit (1);
	close_all_fds(tools);
	ft_execute(smth, env);
}

void	ft_mid_child_pipe(t_transformer *smth, t_env *env, t_tools *tools, \
int i)
{
	mid_has_fdin_redirection(smth, tools, i);
	if (smth->fdout == -2)
	{
		dup2(tools->fd[i + 1][WRITE_END], STDOUT_FILENO);
		close(tools->fd[i][WRITE_END]);
	}
	else
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	close(tools->fd[i + 1][WRITE_END]);
	close(tools->fd[i][READ_END]);
	if (smth->fdin == -1 || smth->fdout == -1)
		exit (1);
	close_all_fds(tools);
	ft_execute(smth, env);
}

void	mid_has_fdin_redirection(t_transformer *smth, t_tools *tools, int i)
{
	if (smth->fdin == -2)
	{
		dup2(tools->fd[i][READ_END], STDIN_FILENO);
		close(tools->fd[i][READ_END]);
	}
	else
	{
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
}

void	ft_bastard(t_transformer *smth, t_env *env, t_tools *tools, int i)
{
	if (smth->fdin == -2)
		dup2(tools->fd[i][READ_END], STDIN_FILENO);
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
	close(tools->fd[i][READ_END]);
	if (smth->fdin == -1 || smth->fdout == -1)
		exit (1);
	close_all_fds(tools);
	free(tools->pid);
	free(tools);
	ft_execute(smth, env);
}
