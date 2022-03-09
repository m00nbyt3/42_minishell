/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:57:01 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/09 15:02:13 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vectorize_flags(t_totems *input, int sect);
int		count_flags(t_totems *input, int sect);
void	print_vector(t_totems *input, int sect);

void	vectorize_flags(t_totems *input, int sect)
{
	char	**vector;
	int		size;
	void	*orig;
	int		i;

	size = count_flags(input, sect);
	vector = malloc((size + 1) * sizeof(char *));
	orig = input;
	i = 0;
	while (input)
	{
		if (input->type == 'f' && input->section == sect)
		{
			vector[i] = ft_strdup(input->content);
			i++;
		}
		input = input->next;
	}
	vector[i] = 0;
	input = orig;
	while (input->type != 'c' || input->section != sect)
		input = input->next;
	input->flags = vector;
	input = orig;
}

int	count_flags(t_totems *input, int sect)
{
	void	*orig;
	int		size;

	orig = input;
	size = 0;
	while (input)
	{
		if (input->type == 'f' && input->section == sect)
			size++;
		input = input->next;
	}
	input = orig;
	return (size);
}

void	print_vector(t_totems *input, int sect)
{
	void	*orig;
	int		i;

	orig = input;
	i = 0;
	while (input)
	{
		if (input->type == 'c' && input->section == sect)
		{
			while (input->flags[i])
			{
				printf("Det: %s (Section %d)\n", \
					input->flags[i], input->section);
				i++;
			}
			break ;
		}
		input = input->next;
	}
	input = orig;
}
