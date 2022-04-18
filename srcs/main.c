/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:01 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/18 12:31:12 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sign(int sig);
void	ctrl_d(char *str);
char	*read_my_line(char *str);

int	main(void)
{
	extern char		**environ;
	char			*str;
	t_list			*env;
	t_totems		*input;
	t_transformer	*runner;

	env = store_env_in_list(environ);
	while (42)
	{
		signal(SIGINT, sign);
		signal(SIGQUIT, sign);
		str = read_my_line(str);
		ctrl_d(str);
		add_history(str);
		if (!ft_chk_quotes(str))
			input = sp_split(str);
		runner = transform(input);
		if (input)
		{
			ft_pipes(&runner, environ, input, env);
			ft_clear_input(&input, free);
		}
		free(str);
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

void	ctrl_d(char *str)
{
	if (str == NULL)
	{
		if (g_util.ctr_c == 0 || g_util.ctr_b == 0)
			exit(0);
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
