/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:38:02 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/03 15:50:04 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_add_totem(t_totems **input, t_totems *new);
void		ft_print_totems(t_totems *input);
void		ft_clear_input(t_totems **input, void (*del)(void *));

void		ft_add_totem(t_totems **input, t_totems *new)
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
	while (input)
	{
		printf("Str: %s.   Type: %c\n", input->content, input->type);
		input = input->next;
	}
}

void	ft_clear_input(t_totems **input, void (*del)(void *))
{
	t_totems	*next;

	if (!del || !input)
		return ;
	while (*input)
	{
		next = (*input)->next;
		free((*input)->content);
		free(*input);
		(*input) = next;
	}
	*input = NULL;
}