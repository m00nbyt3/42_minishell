/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:36:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/28 12:13:16 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_totems	*sp_split(char *s);
char		*char_detection(char *tmp, t_oncreate *shared, \
			t_totems *totem, int *i);
int			is_special_c(char *str, t_totems *totem, int i, t_oncreate *shared);
int			is_redirection(char *str, t_totems *totem, int i);
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
	int	redir;

	while (*str == ' ' && *str)
		str++;
	if (is_redirection(str, totem, i))
		;
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

int	is_redirection(char *str, t_totems *totem, int i)
{
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
	else
		return (0);
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
	input = orig;
}
