/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:34:51 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/04 11:54:40 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxdup(char **mtx)
{
	char	**ret;
	int		i;

	ret = malloc((ft_mtxlen(mtx) + 1) * sizeof(char *));
	i = 0;
	while (mtx[i])
	{
		ret[i] = ft_strdup(mtx[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
