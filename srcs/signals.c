/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:53:49 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/13 12:21:48 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sign(int sig);
void	ctrl_d(char *str, t_transformer *runner);

void	ctrl_d(char *str, t_transformer *runner)
{
	if (str == NULL)
	{
		if (g_util.ctr_c == 0 || g_util.ctr_b == 0)
		{
			ft_clear_transformer(&runner, free);
			ft_putstr_fd("exit", 0);
			exit(0);
		}
	}
}

void	sign(int sig)
{
	char	*str;

	if (sig == SIGINT)
	{
		g_util.ctr_c = 1;
		g_util.exit_value = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_util.ctr_c = 1;
	}
}
