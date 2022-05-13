/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:27:16 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/13 21:17:14 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_quotes(char *str, t_oncreate *shared);
char	*inside_quote(char *str, char **tmp, t_oncreate *shared, int *force);

char	*set_quotes(char *str, t_oncreate *shared)
{
	char	*tmp;
	int		force;

	tmp = 0;
	force = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str = inside_quote(str, &tmp, shared, &force);
		else
		{
			shared->qtype = 0;
			tmp = chr2str(*str, tmp, &force);
		}
		str++;
	}
	if (tmp)
		return (tmp);
	else
		return (ft_strdup(str));
}

char	*inside_quote(char *str, char **tmp, t_oncreate *shared, int *force)
{
	char	qtype = *str;
	str++;
	if (!(*force))
			shared->qtype = qtype;
	while (*str != qtype)
	{
		*tmp = chr2str(*str, *tmp, force);
		str++;
	}
	return (str);
}
