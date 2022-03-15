/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:41:32 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/15 15:29:19 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_cmd(t_totems *input, t_transformer *runner);

t_transformer	*transform(t_totems *input)
{
	t_transformer	*runner;
	t_transformer	*orig;
	int	lap;

	orig = runner;
	lap = 0;
	runner = malloc(sizeof(t_transformer));

	while (input)
	{
		if (lap != input->section)
		{
			runner->next = malloc(sizeof(t_transformer));
			runner = runner->next;
			lap++;
		}
		if (input->type == 'c')
		{
			find_cmd(input, runner);
			vectorize_flags(runner, input, input->section);
		}
		//if (input->content == 'i' || input->content == 'o')
			//find_fds(input, runner);
		input = input->next;
	}
	//print_vector(orig);
	return (orig);
}

void	find_cmd(t_totems *input, t_transformer *runner)
{
	runner->cmd = input->content;
}	

void	find_args(t_totems *input, t_transformer *runner)
{

}
