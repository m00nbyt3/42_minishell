/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:44:56 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/07 17:25:02 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_transformer *smth, int cond);

void	ft_error(t_transformer *smth, int cond)
{
	//liberar elemento
	if (cond == 1)
	{
		write(2, "W4V3shell: ", 11);
		ft_putstr_fd(smth->cmd, 2);
		perror(" ");
		g_util.exit_value = 1;
	}
	exit (1);
}
