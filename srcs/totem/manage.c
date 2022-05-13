/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:38:02 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/13 21:19:35 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_add_totem(t_totems **input, t_totems *new);
void		ft_print_totems(t_totems *input);
void		ft_clear_input(t_totems **input, void (*del)(void *));
void   		ft_clear_transformer(t_transformer **runner, void (*del)(void *));

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
		free((*input)->content);
		free(*input);
		(*input) = next;
	}
	*input = NULL;
}

void    ft_clear_transformer(t_transformer **runner, void (*del)(void *))
{
   /* t_transformer    *next;

    if (!del || !runner)
        return ;
    while (*runner)
    {
        next = (*runner)->next;
    //    free((*runner)->cmd);
    //    if ((*runner)->heredoc)
    //        free((*runner)->heredoc);
//        if ((*runner)->append)
//            free((*runner)->append);
    //    if ((*runner)->flags)
    //        ft_free_matrix((*runner)->flags);
       // free(*runner);
        //(*runner) = next;
    }
    *runner = NULL;*/
}
