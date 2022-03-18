/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:41:32 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/18 12:38:02 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_transformer	*transform(t_totems *input);

t_transformer	*transform(t_totems *input)
{
	t_transformer	*runner;
	t_transformer	*orig;
	int	lap;

	runner = malloc(sizeof(t_transformer));
	orig = runner;
	lap = 0;

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
			runner->cmd = input->content;
			vectorize_flags(runner, input, input->section);
		}
		//if (input->content == 'i' || input->content == 'o')
			//find_fds(input, runner);
		input = input->next;
	}
	runner->next = 0;
	return (orig);
}

