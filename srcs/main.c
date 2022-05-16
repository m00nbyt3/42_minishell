/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:05 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/16 18:48:12 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_my_line(char *str);
void	parse_line(t_totems **input, t_transformer **runner, t_env *env, \
char *str);
void	execution(t_totems **input, t_transformer **runner, t_env *env);

void	leaks(void)
{
	system("leaks minishell");
}

int	main(void)
{
	char			*str;
	t_env			*env;
	t_totems		*input;
	t_transformer	*runner;

	str = 0;
	runner = 0;
	env = store_environ();
	g_util = malloc(1 * sizeof(t_global));
	while (42)
	{
		signal(SIGINT, sign);
		signal(SIGQUIT, sign);
		str = read_my_line(str);
		ctrl_d(str);
		add_history(str);
		parse_line(&input, &runner, env, str);
		execution(&input, &runner, env);
		free(str);
	}
}

void	parse_line(t_totems **input, t_transformer **runner, t_env *env, \
char *str)
{
	*input = 0;
	g_util->ofdin = -1;
	g_util->ofdout = -1;
	g_util->pwd = getcwd(0, 0);
	if (!ft_chk_quotes(str) && !checkreds(str))
		*input = sp_split(str, 0, 0, 0);
	*runner = transform(*input, env);
}

void	execution(t_totems **input, t_transformer **runner, t_env *env)
{
	if (*input && checkargs(*runner, env))
	{
		ft_pipes(runner, env);
		ft_clear_transformer(runner, free);
		ft_clear_input(input, free);
	}
	g_util->ctr_c = 0;
	g_util->ctr_b = 0;
	close(g_util->ofdin);
	close(g_util->ofdout);
	free(g_util->pwd);
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
