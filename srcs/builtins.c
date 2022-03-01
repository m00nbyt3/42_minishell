/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/01 15:30:46 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins(char *input, t_list **env)
{
	if (ft_strcmp(input, "env"))
		ft_env(env);
	/*if (ft_strcmp(args->content, "echo"))
		ft_echo(history);*/
}

void	ft_env(t_list **env)
{
	ft_print_lst(*env);
}

/*void ft_echo(t_list **args)
{}*/
