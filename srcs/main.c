/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:01 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/21 15:47:27 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sign(int sig);
void	ctrl_d(char *str, t_transformer *runner);
char	*read_my_line(char *str);

int	main(void)
{
	extern char		**environ;
	char			*str;
	t_totems		*input;
	t_transformer	*runner;

	while (42)
	{
		signal(SIGINT, sign);
		signal(SIGQUIT, sign);
		str = read_my_line(str);
		ctrl_d(str, runner);
		add_history(str);
		if (!ft_chk_quotes(str))
			input = sp_split(str);
		runner = transform(input);
		if (input)
		{
			ft_pipes(&runner, environ, input);
			ft_clear_input(&input, free);
		}
		free(str);
		ft_clear_transformer(&runner, free);
		g_util.ctr_c = 0;
		g_util.ctr_b = 0;
	}
}

char	*read_my_line(char *str)
{
	str = NULL;
	if (str)
	{
		free(str);
		str = NULL;
	}
	str = readline("W4V3shell# ");
	return (str);
}

void	ctrl_d(char *str, t_transformer *runner)
{
	if (str == NULL)
	{
		if (g_util.ctr_c == 0 || g_util.ctr_b == 0)
		{
			ft_clear_transformer(&runner, free);
			exit(0);
		}
	}
}

//mirar rl_replace_line
void	sign(int sig)
{
	if (sig == SIGINT)
	{
		g_util.ctr_c = 1;
		rl_on_new_line();
		ft_putstr_fd("\nminishell# ", 0);
	}
	if (sig == SIGQUIT)
	{
		g_util.ctr_b = 1;
		ft_putstr_fd("\b\b", 1);
		signal(SIGQUIT, SIG_IGN);
	}
}
