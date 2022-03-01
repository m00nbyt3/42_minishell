/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:01 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/01 16:59:13 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	extern char	**environ;
	char		*str;
	t_list		*env;
	t_list		*args;

	env = store_env_in_list(environ);
	args = NULL;
	while(42)
	{
		str = readline("ミニシェル$ ");
		args = ft_lstnew(str);
		ft_chk_quotes(args);
		ft_builtins(str, &env);
		free(args->content);
		free(args);
	}
}
