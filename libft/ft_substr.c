/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:05:39 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/21 13:33:04 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s) - 1)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start - 1)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < len && start + i < ft_strlen(s))
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
