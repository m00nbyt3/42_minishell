/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:44:56 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/06 11:45:36 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_transformer *smth, int cond);

void	ft_error(t_transformer *smth, int cond)
{
	//liberar elemento

	if (cond == 1)
	{
		dprintf(2,"minishell: %s", smth->cmd);
		perror(" ");
	}
	exit (1);
}
