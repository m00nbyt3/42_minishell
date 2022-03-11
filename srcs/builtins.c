/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/11 17:02:45 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins(t_totems *input, t_list **env);
void	ft_env(t_list **env);
void 	ft_echo(t_totems *input, int section);

void	ft_builtins(t_totems *input, t_list **env)
{
	void	*orig;

	orig = input;
	while (input)
	{
		if (input->type == 'c')
		{
			if (ft_strcmp(input->content, "env"))
			ft_print_lst(*env);
			if (ft_strcmp(input->content, "echo"))
			ft_echo(input, input->section);
		}
		input = input->next;
	}
	input = orig;
}

void	ft_env(t_list **env)
{
	ft_print_lst(*env);
}

void ft_echo(t_totems *input, int section)
{
	void	*orig;

	orig = input;
	while (input && input->section == section)
	{
		if (input->type == 'a')
			printf("%s ", input->content);
		input = input->next;
	}
	printf("\n");
	input = orig;
}
