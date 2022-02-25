/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:25:54 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/21 13:25:59 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;
	char	*hay;

	hay = (char *)haystack;
	i = 0;
	if (needle[i] == '\0' || haystack == needle)
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		n = 0;
		while (hay[i + n] != '\0' && needle[n] != '\0'
			&& needle[n] == hay[i + n] && (i + n) < len)
			n++;
		if (n == ft_strlen(needle))
			return (hay + i);
		i++;
	}
	return (0);
}
