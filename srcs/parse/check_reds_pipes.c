/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reds_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:12:11 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/13 21:03:12 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		checkreds(char *str);
int		checkpipes(char *str, int count, int things, int err);

int	checkreds(char *str)
{
	int	smaller;
	int	bigger;
	int	i;
	int	first;

	if (!checkpipes(str, 0, 0, 0))
		return (1);
	smaller = 0;
	bigger = 0;
	while (*str)
	{
		if (*str == '<')
			smaller++;
		else if (*str == '>')
			bigger++;
		else if (*str == '|')
		{
			if ((smaller || bigger) && !first)
				return (rederror());
			smaller = 0;
			bigger = 0;
			first = 0;
		}
		else
		{
			smaller = 0;
			bigger = 0;
			first++;
		}
		if (smaller && bigger)
			return (rederror());
		if (smaller > 2 || bigger > 2)
			return (rederror());
		str++;
	}
	if ((smaller || bigger) && !first)
		return (rederror());
	return (0);
}

int	checkpipes(char *str, int count, int things, int err)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		err++;
	while (str[i])
	{
		if (str[i] == '|')
		{
			count++;
			things = 0;
		}
		else
			things++;
		i++;
	}
	if ((things == 0 || err) && i)
	{
		write(2, "W4V3shell: syntax error near unexpected token `|'\n", 50);
		g_util.exit_value = 1;
		return (0);
	}
	else
		return (1);
}
