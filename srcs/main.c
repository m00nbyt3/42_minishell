/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/09 18:08:13 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sign(int sig);
void	ctrl_d(char *str, t_transformer *runner);
char	*read_my_line(char *str);
int		checkreds(char *str);
int		checkpipes(char *str, int count, int things, int err);

int	main(void)
{
	char			*str;
	t_env			*env;
	t_totems		*input;
	t_transformer	*runner;

	env = store_environ();
	while (42)
	{
		signal(SIGINT, sign);
		signal(SIGQUIT, sign);
		str = read_my_line(str);
		ctrl_d(str, runner);
		add_history(str);
		input = 0;
		if (!ft_chk_quotes(str) && !checkreds(str))
			input = sp_split(str);
		runner = transform(input, env);
		if (input && checkargs(runner))
		{
			ft_pipes(&runner, input, env);
			ft_clear_input(&input, free);
		}
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
			ft_putstr_fd("exit", 0);
			exit(0);
		}
	}
}

void	sign(int sig)
{
	char *str;
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
	/*smaller = 0;
	bigger = 0;
	first = 1;
	while (*str)
	{
		i++;
		if (*str == '|')
		{
			if ((smaller || bigger) && !first)
				return (1);
			smaller = 0;
			bigger = 0;
			first = 0;
			str++;
		}
		if (*str == '<')
			smaller++;
		else if (*str == '>')
			bigger++;
		else if (!smaller && !bigger && *str != ' ')
		{
			smaller = 0;
			bigger = 0;
			first++;
		}
		if (smaller && bigger && !first)
			return (1);
		if (smaller > 2 || bigger > 2)
			return (1);
		str++;
	}
	if ((smaller || bigger) && !first)
		return (1);
	return (0);*/
}

int	checkpipes(char *str, int count, int things, int err)
{
	if (*str == '|')
		err++;
	while (*str)
	{
		if (*str == '|')
		{
			count++;
			things = 0;
		}
		else
			things++;
		str++;
	}
	if (things == 0 || err)
	{
		write(2, "W4V3shell: syntax error near unexpected token `|'\n", 50);
		g_util.exit_value = 1;
		return (0);
	}
	else
		return (1);
}
