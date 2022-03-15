/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:01 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/15 15:24:03 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	extern char		**environ;
	char			*str;
	t_list			*env;
	t_totems		*input;
	t_transformer	*runner;

	env = store_env_in_list(environ);
	while(42)
	{
		str = readline("ミニシェル# ");
		add_history(str);
		if(!ft_chk_quotes(str))
			input = sp_split(str);
		//ft_print_totems(input);
		ft_builtins(input, &env);
		runner =  transform(input);
		ft_clear_input(&input, free);
	}
}
