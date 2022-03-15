/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:57:01 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/15 15:18:24 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vectorize_flags(t_transformer *runner, t_totems *input, int sect);
void	save_flag(t_totems *input, int sect, char **vector, int *i);
int		count_flags(t_totems *input, int sect);
void	print_vector(t_transformer *runner);

void	vectorize_flags(t_transformer *runner, t_totems *input, int sect)
{
	char	**vector;
	int		size;
	void	*orig;
	int		i;

	size = count_flags(input, sect) + 1;
	vector = malloc((size + 1) * sizeof(char *));
	orig = input;
	i = 0;
	while (input)
	{
		save_flag(input, sect, vector, &i);
		input = input->next;
	}
	vector[i] = 0;
	input = orig;
	while (input->type != 'c' || input->section != sect)
		input = input->next;
	runner->flags = vector;
	input = orig;
}

void	save_flag(t_totems *input, int sect, char **vector, int *i)
{
	if ((input->type == 'f' || input->type == 'a' || input->type == 'c') \
		&& input->section == sect)
	{
		vector[*i] = ft_strdup(input->content);
		if (input->type == 'f')
			vector[*i] = ft_strjoin("-\0", vector[*i]);
		(*i)++;
	}
}

int	count_flags(t_totems *input, int sect)
{
	void	*orig;
	int		size;

	orig = input;
	size = 0;
	while (input)
	{
		if ((input->type == 'f' || input->type == 'a') \
		&& input->section == sect)
			size++;
		input = input->next;
	}
	input = orig;
	return (size);
}

void	print_vector(t_transformer *runner)
{
	void	*orig;
	int		i;

	orig = runner;
	i = 0;
	while (runner)
	{
		printf("%s\n", runner->cmd);
		while (runner->flags[i])
		{
			printf("%s\n", runner->flags[i]);
			i++;
		}
		runner = runner->next;
	}
	runner = orig;
}
