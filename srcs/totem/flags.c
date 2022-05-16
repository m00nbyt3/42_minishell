/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:57:01 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/16 18:58:29 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vectorize_flags(t_transformer *runner, t_totems *input, \
	int sect, t_env *env);
int		save_flag(t_totems *input, int sect, char **vector, t_env *env);
int		count_flags(t_totems *input, int sect);
void	print_vector(t_transformer *runner);
char	*getdollars(char *str, t_env *env);
int		expand_dollar(char **aux, t_env *env, char **ret);

void	vectorize_flags(t_transformer *runner, t_totems *input, \
	int sect, t_env *env)
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
		if (save_flag(input, sect, &vector[i], env))
			i++;
		input = input->next;
	}
	vector[i] = 0;
	input = orig;
	while (input->type != 'c' || input->section != sect)
		input = input->next;
	runner->flags = vector;
	input = orig;
}

int	save_flag(t_totems *input, int sect, char **vector, t_env *env)
{
	char	*str;

	if ((input->type == 'f' || input->type == 'a' || input->type == 'c') \
		&& input->section == sect)
	{
		*vector = input->content;
		if (**vector == '$' && input->qtype != '\'' && input->type != 'h')
		{
			input->content = getdollars(*vector, env);
			*vector = input->content;
		}
		if (input->type == 'f')
		{
			str = ft_strjoin("-\0", *vector);
			free(input->content);
			input->content = str;
			*vector = input->content;
		}
		return (1);
	}
	return (0);
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
	while (runner)
	{
		printf("Command: %s\n", runner->cmd);
		i = 0;
		while (runner->flags[i])
		{
			printf("%s\n", runner->flags[i]);
			i++;
		}
		runner = runner->next;
	}
	runner = orig;
}
