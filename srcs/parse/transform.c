/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:41:32 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/21 14:28:54 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_transformer	*transform(t_totems *input);
void	find_fds(t_totems *input, t_transformer *runner);

t_transformer	*transform(t_totems *input)
{
	t_transformer	*runner;
	t_transformer	*orig;
	int	lap;

	runner = malloc(sizeof(t_transformer));
	orig = runner;
	lap = 0;
	runner->fdin = 0;
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
		if (input->type == 'i' || input->type == 'o')
			find_fds(input, runner);
		input = input->next;
	}
	runner->fdout = 1;
	runner->next = 0;
	return (orig);
}

void	find_fds(t_totems *input, t_transformer *runner)
{
	//Comprobar archivo existe
	if (input->type == 'i')
		runner->fdin = open(input->content, O_RDONLY);
	if (input->type == 'o')
		runner->fdout = open(input->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
}

