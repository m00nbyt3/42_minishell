/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:27:35 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/21 13:27:39 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	val;
	long	num;
	long	i;

	i = 0;
	num = 0;
	val = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			val = -1;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		num = num * 10 + (str[i++] - '0');
		if ((num * val) > 2147483647)
			return (-1);
		if ((num * val) < -2147483648)
			return (0);
	}
	return (num * val);
}
