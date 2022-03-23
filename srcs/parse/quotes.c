/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/22 12:29:18 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_chk_quotes(char *str);
void	last_quote(char c, t_oncreate *shared);
char	*remove_quotes(char *str, t_oncreate *shared);
size_t	count_quotes(char *str, t_oncreate *shared);

int	ft_chk_quotes(char *str)
{
	int		i;
	int		scount;
	int		dcount;

	i = 0;
	scount = 0;
	dcount = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !(dcount % 2))
			scount++;
		if (str[i] == '\"' && !(scount % 2))
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
}

char	*remove_quotes(char *str, t_oncreate *shared)
{
	size_t	qcount;
	void	*orig;
	char	*mod;
	char	*new;

	qcount = count_quotes(str, shared);
	if (!qcount)
		return (ft_strdup(str));
	new = malloc((ft_strlen(str) - qcount + 1) * sizeof(char));
	mod = new;
	orig = str;
	while (*str)
	{
		if (*str != shared->qtype)
		{
			*mod = *str;
			mod++;
		}
		str++;
	}
	*mod = 0;
	return (new);
}

size_t	count_quotes(char *str, t_oncreate *shared)
{
	size_t	qcount;
	void	*orig;

	orig = str;
	qcount = 0;
	while (*str)
	{
		if (*str == shared->qtype)
			qcount++;
		str++;
	}
	str = orig;
	return (qcount);
}
