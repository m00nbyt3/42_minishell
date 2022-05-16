/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 17:33:04 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/16 17:00:23 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **mtrx)
{
	int	i;

	i = 0;
	while (mtrx[i])
	{
		free(mtrx[i]);
		i++;
	}
	free(mtrx);
}

void	ft_free_mtxbasic(char **mtrx)
{
	int	i;

	i = 0;
	while (mtrx[i])
	{
		free(mtrx[i]);
		i++;
	}
}
