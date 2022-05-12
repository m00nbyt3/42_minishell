/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:42:49 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/12 13:34:41 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxcat(char **mtx, char *str)
{
	char	**new;
	int		i;

	new = malloc((ft_mtxlen(mtx) + 2) * sizeof(char *));
	i = 0;
	while (mtx[i])
	{
		new[i] = mtx[i];
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = 0;
	return (new);
}
