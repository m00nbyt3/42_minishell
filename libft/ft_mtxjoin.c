/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:32:42 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/16 16:12:37 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxjoin(char **m1, char **m2)
{
	char	**joined;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!m2)
		return (NULL);
	len1 = ft_mtxlen(m1);
	len2 = ft_mtxlen(m2);
	joined = ft_calloc(sizeof(char *), (len1 + len2 + 1));
	i = 0;
	while (m1[i])
	{
		joined[i] = ft_strdup(m1[i]);
		i++;
	}
	j = 0;
	while (m2[j])
	{
		joined[i] = ft_strdup(m2[j]);
		i++;
		j++;
	}
	return (joined);
}
