/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:01:41 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/04 12:45:00 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (unsigned char *)dest == (unsigned char *)src)
		return ((unsigned char *)dest);
	while (n-- != 0)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return ((unsigned char *)dest);
}
