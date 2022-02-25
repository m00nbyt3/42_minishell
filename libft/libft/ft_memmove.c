/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:35:14 by agallipo          #+#    #+#             */
/*   Updated: 2021/09/23 11:30:58 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*aux_dest;
	unsigned char	*aux_src;

	aux_dest = ((unsigned char *)dest);
	aux_src = ((unsigned char *)src);
	i = 0;
	if (aux_dest > aux_src)
	{
		while (len-- != 0)
		{
			aux_dest[len] = aux_src[len];
		}
	}
	else
		ft_memcpy(aux_dest, aux_src, len);
	return (aux_dest);
}
