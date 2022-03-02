/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/02 17:20:12 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins(char *input, t_list **env);
void	ft_env(t_list **env);

void	ft_builtins(char *input, t_list **env)
{
	if (ft_strcmp(input, "env"))
		ft_env(env);
	/*if (ft_strcmp(args->content, "echo"))
		ft_echo(input);*/
}

void	ft_env(t_list **env)
{
	ft_print_lst(*env);
}

/*void ft_echo(t_list **args)
{}*/
