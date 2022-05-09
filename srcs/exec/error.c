/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:44:56 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/09 15:02:59 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_transformer *smth, int cond);
int		rederror(void);

void	ft_error(t_transformer *smth, int cond)
{
	//liberar elemento
	if (cond == 1)
	{
		write(2, "W4V3shells: ", 12);
		ft_putstr_fd(smth->cmd, 2);
		perror(" ");
		write(2, "\n", 1);
		g_util.exit_value = 1;
	}
}

int	rederror(void)
{
	write(2, "W4V3shells: ", 12);
	ft_putstr_fd("syntax error near unexpected token (< or >)", 2);
	write(2, "\n", 1);
	g_util.exit_value = 258;
	return (1);
}
