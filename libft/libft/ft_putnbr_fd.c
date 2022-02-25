/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:37:45 by agallipo          #+#    #+#             */
/*   Updated: 2021/06/21 13:48:48 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr == -2147483648)
		write(fd, "-2147483648", 11);
	if (nbr != -2147483648)
	{
		if (nbr < 0)
		{
			ft_putchar_fd('-', fd);
			nbr = -nbr;
		}
		if (nbr >= 10)
		{
			ft_putnbr_fd(nbr / 10, fd);
			ft_putnbr_fd(nbr % 10, fd);
		}
		else
			ft_putchar_fd(nbr + '0', fd);
	}
}
