/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:36:17 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/15 13:36:24 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*new_element(char *s, t_totems **input, t_oncreate *shared);
char		*set_totem_type(char *tmp, t_oncreate *shared, t_totems *totem);

char	*new_element(char *s, t_totems **input, t_oncreate *shared)
{
	t_totems	*totem;
	char		*tmp;
	char		*orig;
	int			i;

	totem = malloc(sizeof(t_totems));
	if (!totem)
		return (0);
	tmp = ft_strdup((const char *)s);
	shared->inquotes = 0;
	shared->qtype = 0;
	totem->type = 0;
	orig = tmp;
	tmp = set_totem_type(tmp, shared, totem);
	totem->content = set_quotes(tmp, shared);
	totem->qtype = shared->qtype;
	totem->next = 0;
	ft_add_totem(input, totem);
	return (orig);
}

char	*set_totem_type(char *tmp, t_oncreate *shared, t_totems *totem)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		last_quote(tmp[i], shared);
		if (!shared->inquotes)
		{
			tmp = char_detection(tmp, shared, totem, &i);
			if (i < 0)
			{
				i *= -1;
				break ;
			}
		}
		else
			i++;
	}
	tmp[i] = 0;
	return (tmp);
}
