/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:57:11 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/21 13:34:44 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_containchar(char *str, char c)
{
	while (*str)
	{
		if (*str++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	i;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == 0)
		return (ft_strdup(""));
	while (*s1)
	{
		if (ft_containchar(set, *s1) == 1)
			s1++;
		else
			break ;
	}
	i = ft_strlen(s1);
	while (i > 0)
	{
		if (ft_containchar(set, *(s1 + i - 1)) == 1)
			i--;
		else
			break ;
	}
	return (ft_substr(s1, 0, i));
}
