/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:36:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/02 20:05:27 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_totems	*sp_split(char *s);
void		new_element (char *s, t_totems **input);
void		ft_add_totem(t_totems **input, t_totems *new);
void		ft_print_totems(t_totems *input);
void		ft_clear_input(t_totems **input, void (*del)(void *));

t_totems	*sp_split(char *s)
{
	t_totems	*input;
	size_t		size;
	size_t		i;

	input = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else
		{
			new_element(&(s[i]), &input);
			while (s[i] != ' ' && s[i])
				i++;
		}
	}
	return(input);
}

void	new_element(char *s, t_totems **input)
{
	t_totems	*totem;
	char		*tmp;
	char		*orig;
	int			inquotes;

	tmp = ft_strdup((const char *)s);
	orig = tmp;
	inquotes = 0;
	while (*tmp)
	{
		if (*tmp == '\"' || *tmp == '\'')
			inquotes = !inquotes;
		if (!inquotes && *tmp == ' ') //&& is_special_c(*s))
			break;
		tmp++;
	}
	*tmp = 0;
	totem = malloc(sizeof(t_totems));
	if (!totem)
		return ;
	totem->content = ft_strdup((const char *)orig);
	free(orig);
	totem->type = 3;
	totem->next = 0;
	ft_add_totem(input, totem);
}

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
		printf("Str: %s   Type: %d\n", input->content, input->type);
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