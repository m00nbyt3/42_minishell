/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:01:29 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/04 12:49:26 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!(unsigned char *)dest && !(unsigned char *)src)
			return (NULL);
		if (((unsigned char *)src)[i] == (unsigned char)c)
		{
			(((unsigned char *)dest)[i]) = (((unsigned char *)src)[i]);
			return ((unsigned char *)dest + ++i);
		}
		(((unsigned char *)dest)[i]) = (((unsigned char *)src)[i]);
		i++;
	}
	return (NULL);
}
