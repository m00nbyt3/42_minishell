/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/08 12:02:37 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_chk_quotes(char *str);
char	*remove_quotes(char *str);
void	last_quote(char c, t_oncreate *shared);

int	ft_chk_quotes(char *str)
{
	int	i;
	int	scount;
	int	dcount;

	i = 0;
	scount = 0;
	dcount = 0;
	while(str[i])
	{
		if (str[i] == '\'')
			scount++;
		if (str[i] == '\"')
			dcount++;
		i++;
	}
	if (scount % 2 || dcount % 2)
	{
		ft_putstr_fd("Error (invalid quotation)\n", 1);
		return (1);
	}
	return (0);
}

void	last_quote(char c, t_oncreate *shared)
{
	if (shared->inquotes)
	{
		if (c == shared->qtype)
			shared->inquotes = 0;
	}
	else if (c == '\"' || c == '\'')
	{
		shared->qtype = c;
		shared->inquotes = 1;
	}
	return ;
}

char	*remove_quotes(char *str)
{
	int	pos;
	char *mod;

	mod = ft_strdup(str);
	if (*mod == '\"' || *mod == '\'')
		mod++;
	pos = ft_strlen(mod) - 1;
	if (mod[pos] == '\"' || mod[pos] == '\'')
		mod[pos] = 0;
	return(mod);
}
