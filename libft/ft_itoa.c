/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 19:45:06 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/17 12:14:08 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_of_digit(int n)
{
	int	digit;

	digit = 1;
	if (n < 0)
	{
		digit += 1;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static char	*ft_check_error(int n, char *number)
{
	if (n < 0)
	{
		number[0] = '-';
	}
	if (n == 0)
		number[0] = '0';
	return (number);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		digit;

	digit = ft_num_of_digit(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	number = (char *)malloc((digit + 1) * sizeof(char));
	if (!number)
		return (NULL);
	number[digit] = '\0';
	number = ft_check_error(n, number);
	if (n < 0)
		n *= -1;
	while (digit > 0)
	{
		digit--;
		if (digit == 0 && number[0] == '-')
			break ;
		number[digit] = (n % 10) + '0';
		n /= 10;
	}
	return (number);
}
