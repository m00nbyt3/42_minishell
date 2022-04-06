/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:52:39 by ycarro            #+#    #+#             */
/*   Updated: 2022/04/06 15:22:44 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_frst_child_pipe(t_transformer *smth, char **env, int *fd);
void	ft_mid_child_pipe(t_transformer *smth, char **env, int *fd1, int *fd2);
void	ft_bastard(t_transformer *smth, char **env, int *fd1);

void	ft_frst_child_pipe(t_transformer *smth, char **env, int *fd)
{
	close(fd[READ_END]);
	if (smth->fdin != -2 && !smth->heredoc)
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
	if (smth->fdin == -1 || smth->fdout == -1)
		ft_error(smth, 0);
	ft_execute(smth, env);
}

void	ft_mid_child_pipe(t_transformer *smth, char **env, int *fd1, int *fd2)
{
	if (smth->fdin == -2 && !smth->heredoc)
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
	if (smth->fdin == -1 || smth->fdout == -1)
		ft_error(smth, 0);
	ft_execute(smth, env);
}

void	ft_bastard(t_transformer *smth, char **env, int *fd1)
{
	if (smth->fdin == -2 && !smth->heredoc)
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
	if (smth->fdin == -1 || smth->fdout == -1)
		ft_error(smth, 0);
	ft_execute(smth, env);
}
