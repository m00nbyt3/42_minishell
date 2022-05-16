/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:38:02 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/16 13:04:57 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_add_totem(t_totems **input, t_totems *new);
void		ft_print_totems(t_totems *input);
void		ft_clear_input(t_totems **input, void (*del)(void *));
void		ft_clear_transformer(t_transformer **orig, void (*del)(void *));
void		free_this(void *ptr);


void	ft_add_totem(t_totems **input, t_totems *new)
{
	t_totems	*last;

	last = *input;
	if (input && new)
	{
		if (!(*input))
			*input = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
}

void	ft_print_totems(t_totems *input)
{
	void	*orig;

	orig = input;
	while (input)
	{
		printf("Str: %s.   Type: %c   Section: %d	Quotes: %c.\n", \
			input->content, input->type, input->section, input->qtype);
		input = input->next;
	}
	input = orig;
}

void	ft_clear_input(t_totems **input, void (*del)(void *))
{
	t_totems	*next;

	if (!del || !input)
		return ;
	while (*input)
	{
		next = (*input)->next;
		if ((*input)->content)
			free((*input)->content);
		free(*input);
		(*input) = next;
	}
	*input = NULL;
}

void	ft_clear_transformer(t_transformer **orig, void (*del)(void *))
{
	t_transformer	*runner;
	void			*tmp;

	runner = *orig;
    if (!del || !runner)
        return ;
    while (runner)
    {
    	free(runner->flags);
    	tmp = runner;
        runner = runner->next;
    	free(tmp);
    	tmp = NULL;
    }
}

void	free_this(void *ptr)
{
	free(ptr);
	ptr = 0;
}