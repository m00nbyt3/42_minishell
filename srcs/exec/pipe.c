/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:10:30 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/21 14:18:19 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *error, char *arg)
{	
	ft_putstr_fd("ミニシェル: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

void	ft_exit_process(int condition, char *argv)
{
	if (condition == 0)
	{
		ft_print_error("file error", argv);
		exit (0);
	}
	if (condition == 1)
	{
		ft_print_error("command not found", "");
		exit (0);
	}
	if (condition == 2)
	{
		ft_print_error("command not found", argv);
		exit (0);
	}
}
