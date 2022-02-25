/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:24:35 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/21 13:24:38 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	if (!destsize)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	if (!dest)
		return (0);
	while (src[i] != '\0' && (i + 1) < destsize)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
