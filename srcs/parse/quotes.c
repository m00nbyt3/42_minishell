/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/02 15:34:39 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chk_quotes(t_list *args)
{
	int	i;
	int	scount;
	int	dcount;

	i = 0;
	scount = 0;
	dcount = 0;
	while (args->content[i])
	{
		if (args->content[i] == '\'')
			scount++;
		if (args->content[i] == '\"')
			dcount++;
		i++;
	}
	if (scount % 2 || dcount % 2)
		ft_putstr_fd("Error (invalid quotation)\n", 1);
}
