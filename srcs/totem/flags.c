/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:57:01 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/07 19:22:56 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vectorize_flags(t_transformer *runner, t_totems *input, int sect);
void	save_flag(t_totems *input, int sect, char **vector, int *i);
int		count_flags(t_totems *input, int sect);
void	print_vector(t_transformer *runner);
char	*getdollars(char *str);

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
	//clean_quotes(input);
	if ((input->type == 'f' || input->type == 'a' || input->type == 'c') \
		&& input->section == sect)
	{
		vector[*i] = input->content;
		if (input->type == 'f')
			vector[*i] = ft_strjoin("-\0", vector[*i]);
		if (*vector[*i] == '$' && input->qtype != '\'' && input->type != 'h')
			vector[*i] = getdollars(vector[*i]);
		//else
			//vector[*i] = fvck_quotes(vector[*i], input->qtype);
		(*i)++;
	}
}

char	*getdollars(char *str)
{
	char	*aux;
	char	*orig;
	char	*ret;
	int		i;

	orig = ft_strdup(str);
	i = 0;
	ret = ft_calloc(sizeof(char *), 1);
	while (orig[i])
	{
		if (orig[i] == '$')
		{
			aux = ft_strdup(orig + (i + 1));
			cutstr(aux, ' ');
			aux = getenv(aux);
			ret = ft_strjoin(ret, aux);
		}
		i++;
	}
	free(orig);
	return (ret);
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
