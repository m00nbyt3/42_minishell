/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:41:32 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/06 10:53:20 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_transformer	*transform(t_totems *input);
void			find_fds(t_totems *input, t_transformer *runner);
void			create_transformer(t_transformer **runner, int *lap);
void			fill_content(t_totems *input, t_transformer *runner);
void			set_doubles(t_totems *input, t_transformer *runner);

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
	runner->heredoc = 0;
	runner->append = 0;
	while (input)
	{
		if (lap != input->section)
			create_transformer(&runner, &lap);
		if (input->type == 'c')
			fill_content(input, runner);
		if (input->type == 'i' || input->type == 'o')
			find_fds(input, runner);
		if (input->type == 'h' || input->type == 'p')
			set_doubles(input, runner);
		input = input->next;
	}
	runner->next = 0;
	return (orig);
}

void	create_transformer(t_transformer **p_runner, int *lap)
{
	t_transformer	*runner;

	runner = *p_runner;
	runner->next = malloc(sizeof(t_transformer));
	runner = runner->next;
	runner->fdin = -2;
	runner->fdout = -2;
	runner->heredoc = 0;
	runner->append = 0;
	(*lap)++;
	*p_runner = runner;
}

void	fill_content(t_totems *input, t_transformer *runner)
{
	runner->cmd = input->content;
	vectorize_flags(runner, input, input->section);
}

void	find_fds(t_totems *input, t_transformer *runner)
{
	if (input->type == 'i')
		runner->fdin = open(input->content, O_RDONLY);
	if (input->type == 'o')
		runner->fdout = open(input->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (runner->fdout == -1 || runner->fdin == -1)
	{
		write(2, "W4V3shell: ", 11);
		ft_putstr_fd(input->content, 2);
		perror(" ");
	}
}

void	set_doubles(t_totems *input, t_transformer *runner)
{
	if (input->type == 'h')
		runner->heredoc = input->content;
	if (input->type == 'p')
		runner->fdout = open(input->content, O_RDWR | O_CREAT | O_APPEND, 0644);
		//runner->append = input->content;
	if (runner->fdout == -1 || runner->fdin == -1)
	{
		write(2, "W4V3shell: ", 11);
		ft_putstr_fd(input->content, 2);
		perror(" ");
	}
	runner->qtype = input->qtype;
}
