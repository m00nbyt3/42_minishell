/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:48:26 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/13 13:38:35 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_transformer *runner);
int		echo_comp_n(char *str);
void	write_echo(t_transformer *runner, int i);

void	ft_echo(t_transformer *runner)
{
	void	*orig;
	int		newline;
	int		i;

	orig = runner;
	newline = 1;
	i = 1;
	if (*(runner->flags + i) == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	if (echo_comp_n(*(runner->flags + i)))
	{
			newline = 0;
			i++;
	}
	write_echo(runner, i);
	if (newline)
		write(1, "\n", 1);
	runner = orig;
	g_util.exit_value = 0;
}

void	write_echo(t_transformer *runner, int i)
{
	while (*(runner->flags + i))
	{
		if (*(runner->flags + i + 1))
		{
			ft_putstr_fd(*(runner->flags + i), 1);
			write(1, " ", 1);
		}
		else
			ft_putstr_fd(*(runner->flags + i), 1);
		i++;
	}
}

int	echo_comp_n(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}
