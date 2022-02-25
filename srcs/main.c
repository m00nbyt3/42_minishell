/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:01 by agallipo          #+#    #+#             */
/*   Updated: 2022/02/25 17:28:41 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	extern char	**environ;
	char		*str;
	t_list		*env;

	//printf("%s", *environ);
	env = store_env_in_list(environ);
	while(42)
	{
		str = readline("ミニシェル$ ");
		ft_builtins(str, &env);
	}
}
