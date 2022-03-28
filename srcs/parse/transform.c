/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:41:32 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/28 17:40:56 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_transformer	*transform(t_totems *input);
void			find_fds(t_totems *input, t_transformer *runner);
void			create_transformer(t_transformer *runner, int *lap);
void			fill_content(t_totems *input, t_transformer *runner);

t_transformer	*transform(t_totems *input)
{
	t_transformer	*runner;
	t_transformer	*orig;
	int				lap;

	runner = malloc(sizeof(t_transformer));
	orig = runner;
	lap = 0;
	runner->fdin = -2;
	runner->fdout = -2;
	while (input)
	{
		if (lap != input->section)
			create_transformer(runner, &lap);
		if (input->type == 'c')
			fill_content(input, runner);
		if (input->type == 'i' || input->type == 'o')
			find_fds(input, runner);
		input = input->next;
	}
	runner->next = 0;
	return (orig);
}

void	create_transformer(t_transformer *runner, int *lap)
{
	runner = runner->next;
	runner = malloc(sizeof(t_transformer));
	runner->fdin = -2;
	runner->fdout = -2;
	(*lap)++;
}

void	fill_content(t_totems *input, t_transformer *runner)
{
	runner->cmd = input->content;
	vectorize_flags(runner, input, input->section);
}

void	find_fds(t_totems *input, t_transformer *runner)
{
	//Comprobar archivo existe
	if (input->type == 'i')
		runner->fdin = open(input->content, O_RDONLY);
	if (input->type == 'o')
		runner->fdout = open(input->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
}
