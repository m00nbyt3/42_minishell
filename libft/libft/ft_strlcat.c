/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:19:30 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/21 13:50:24 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	ts;
	size_t	td;

	ts = ft_strlen(src);
	td = ft_strlen(dest);
	i = 0;
	if (destsize < (td + 1))
		return (destsize + ts);
	if (destsize > (td + 1))
	{
		while (src[i] != '\0' && (td + i + 1) < destsize)
		{
			dest[td + i] = src[i];
			i++;
		}
	}
	dest[td + i] = '\0';
	return (ts + td);
}
