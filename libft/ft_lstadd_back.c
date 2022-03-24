/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:40:57 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/24 11:34:25 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
}
