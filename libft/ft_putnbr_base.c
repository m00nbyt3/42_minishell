/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:59:47 by agallipo          #+#    #+#             */
/*   Updated: 2022/02/16 17:33:59 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_error(char *base)
{
	int	d;
	int	e;
	int	f;

	e = 0;
	d = ft_strlen(base);
	f = 0;
	if (d <= 1)
		return (1);
	while (base[e] != '\0' && base[f] != '\0' && d > 1)
	{
		while (base[e] != '\0' && base[f] != '\0')
		{
			if ((base[e] == base[f] && e != f) || (base[f] == '+'\
				|| base[f] == '-'))
				return (1);
			f++;
		}
		e++;
		f = 0;
	}
	return (0);
}

void	ft_putnbr_base(unsigned int nbr, char *base)
{
	int	i;
	int	c;

	if (find_error(base) == 0)
	{
		i = ft_strlen(base);
		if (nbr > 0)
		{
			ft_putnbr_base(nbr / i, base);
			c = nbr % i;
			write(1, &base[c], 1);
		}
	}
}
