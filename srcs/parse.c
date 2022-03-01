/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/01 17:34:44 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chk_quotes(t_list *args)
{
	int	i;
	int	count;

	while (args->next)
		args = args->next;
	i = 0;
	while (args->content[i] != 0)
	{
		if (args->content[i] == '\"')
			count++;
		i++;
	}
	if (count % 2 != 0)
		printf("%s\n", "error");
}
