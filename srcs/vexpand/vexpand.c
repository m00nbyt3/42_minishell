/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vexpand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:45:52 by ycarro            #+#    #+#             */
/*   Updated: 2022/04/11 17:14:39 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vexpand(t_transformer *content, char type)
{
	dprintf(2, "HOOOOOOOOOOOO\n");
	if (*content->flags == "$" && type != 'h')
			*content->flags = getenv(*content->flags + 1);
}
