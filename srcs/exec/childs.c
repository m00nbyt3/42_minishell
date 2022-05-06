/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:52:39 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/06 16:30:46 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_frst_child_pipe(t_transformer *smth, t_env *env, t_tools *tools);
void	ft_mid_child_pipe(t_transformer *smth, t_env *env, t_tools *tools, int i);
void	ft_bastard(t_transformer *smth, t_env *env, t_tools *tools, int i);

void	ft_frst_child_pipe(t_transformer *smth, t_env *env,t_tools *tools)
{
	close(tools->fd[0][READ_END]);
	if (smth->fdin != -2)
	{
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
	if (smth->fdout == -2)
	{
		dup2(tools->fd[0][WRITE_END], STDOUT_FILENO);
		close(tools->fd[0][WRITE_END]);
	}
	else
	{
		close(tools->fd[0][WRITE_END]);
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	close(tools->fd[0][WRITE_END]);
	if (smth->fdin == -1 || smth->fdout == -1)
		exit (1);
	close_all_fds(tools, tools->fd[0][READ_END], tools->fd[0][WRITE_END]);
	ft_execute(smth, env);
}

void	ft_mid_child_pipe(t_transformer *smth, t_env *env, t_tools *tools, int i)
{
	if (smth->fdin == -2)
	{
		dup2(tools->fd[i][READ_END], STDIN_FILENO);
		close(tools->fd[i][READ_END]);
	}
	else
	{
		close(tools->fd[i][READ_END]);
		dup2(smth->fdin, STDIN_FILENO);
		close(smth->fdin);
	}
	if (smth->fdout == -2)
	{
		dup2(tools->fd[i + 1][WRITE_END], STDOUT_FILENO);
		close(tools->fd[i + 1][WRITE_END]);
	}
	else
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	close(tools->fd[i][READ_END]);
	if (smth->fdin == -1 || smth->fdout == -1)
		exit (1);
	close_all_fds(tools, tools->fd[i][READ_END], tools->fd[i + 1][WRITE_END]);
	ft_execute(smth, env);
}

void	ft_bastard(t_transformer *smth, t_env *env, t_tools *tools, int i)
{
	if (smth->fdin == -2)
	{
		dup2(tools->fd[i][READ_END], STDIN_FILENO);
		close(tools->fd[i][READ_END]);
	}
	else
	{
		close(tools->fd[i][READ_END]);
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
	close_all_fds(tools, tools->fd[i][READ_END], -42);
	ft_execute(smth, env);
}
