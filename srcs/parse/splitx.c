/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:36:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/09 17:26:17 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_totems	*sp_split(char *s);
char		*new_element(char *s, t_totems **input, t_oncreate *shared);
char		*set_totem_type(char *tmp, t_oncreate *shared, t_totems *totem);
char		*char_detection(char *tmp, t_oncreate *shared, \
			t_totems *totem, int *i);
int			is_special_c(char *str, t_totems *totem, int i, t_oncreate *shared);
void		set_command(t_totems *input, int sect);

t_totems	*sp_split(char *s)
{
	t_oncreate	*shared;
	t_totems	*input;
	char		*used;
	size_t		i;
	int			j;

	shared = malloc(sizeof(t_oncreate));
	shared->section = 0;
	input = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' && s[i])
			i++;
		if (!s[i])
			break ;
		used = new_element(&(s[i]), &input, shared);
		i += ft_strlen(used);
		free(used);
	}
	j = -1;
	while (++j <= shared->section)
		set_command(input, j);
	free(shared);
	return (input);
}

char	*new_element(char *s, t_totems **input, t_oncreate *shared)
{
	t_totems	*totem;
	char		*tmp;
	char		*orig;
	int			i;

	totem = malloc(sizeof(t_totems));
	if (!totem)
		return (0);
	tmp = ft_strdup((const char *)s);
	shared->inquotes = 0;
	totem->type = 0;
	orig = tmp;
	tmp = set_totem_type(tmp, shared, totem);
	totem->content = ft_strdup((const char *)remove_quotes(tmp));
	totem->next = 0;
	ft_add_totem(input, totem);
	return (orig);
}

char	*set_totem_type(char *tmp, t_oncreate *shared, t_totems *totem)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		last_quote(tmp[i], shared);
		if (!shared->inquotes)
		{
			tmp = char_detection(tmp, shared, totem, &i);
			if (i < 0)
			{
				i *= -1;
				break ;
			}
		}
		else
			i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	*char_detection(char *tmp, t_oncreate *shared, t_totems *totem, int *i)
{
	if (is_special_c(&(tmp[*i]), totem, *i, shared))
	{
		if (*i)
		{
			*i *= -1;
			return (tmp);
		}
		if (*(tmp + 1) == '<' || *(tmp + 1) == '>')
			tmp++;
		tmp++;
		while (tmp[*i] == ' ' && tmp[*i])
			tmp++;
		return (tmp);
	}
	else
	{
		if (tmp[*i] == ' ')
		{
			*i *= -1;
			return (tmp);
		}
		(*i)++;
	}
	return (tmp);
}

int	is_special_c(char *str, t_totems *totem, int i, t_oncreate *shared)
{
	while (*str == ' ' && *str)
		str++;
	if (*str == '<')
	{
		if (!i)
		{
			if (*(str + 1) == '<')
				totem->type = 'h';
			else
				totem->type = 'i';
		}
	}
	else if (*str == '>')
	{
		if (!i)
		{
			if (*(str + 1) == '>')
				totem->type = 'p';
			else
				totem->type = 'o';
		}
	}
	else if (*str == '-')
	{
		if (!i)
			totem->type = 'f';
	}
	else if (*str == '|')
	{
		if (!i)
			shared->section++;
	}
	else
	{
		if (!totem->type)
			totem->type = 'a';
		totem->section = shared->section;
		return (0);
	}
	totem->section = shared->section;
	return (1);
}

void	set_command(t_totems *input, int sect)
{
	int		tot;
	void	*orig;
	void	*mod;

	orig = input;
	tot = 0;
	while (input)
	{
		if (input->type == 'a' && input->section == sect)
		{	
			if (!tot)
			{
				input->type = 'c';
				tot++;
			}
		}
		input = input->next;
	}
	if (!tot)
		ft_putstr_fd("Error (no command)\n", 1);
	input = orig;
	vectorize_flags(input, sect);
}
