/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:44:56 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/15 17:57:48 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_transformer *smth, int cond);
int		rederror(void);
void	command_not_found(t_transformer *smth);

//liberar elemento
void	ft_error(t_transformer *smth, int cond)
{
	if (cond == 1)
	{
		write(2, "W4V3shells: ", 12);
		ft_putstr_fd(smth->cmd, 2);
		perror(" ");
		write(2, "\n", 1);
		g_util->exit_value = 1;
	}
}

int	rederror(void)
{
	write(2, "W4V3shells: ", 12);
	ft_putstr_fd("syntax error near unexpected token (< or >)", 2);
	write(2, "\n", 1);
	g_util->exit_value = 258;
	return (1);
}

void	command_not_found(t_transformer *smth)
{
	write(2, "W4V3shell: ", 11);
	ft_putstr_fd(smth->cmd, 2);
	write(2, " : command not found\n", 21);
	g_util->exit_value = 127;
	exit (127);
}
