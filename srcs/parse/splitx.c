/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:36:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/07 17:13:19 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_totems	*sp_split(char *s);
char		*new_element(char *s, t_totems **input, t_oncreate *shared);
int			is_special_c(char *str, t_totems *totem, int i, t_oncreate *shared);
char		*remove_quotes(char *str);
void		check_quotes(char c, t_oncreate *shared);


t_totems	*sp_split(char *s)
{
	t_oncreate	*shared;
	t_totems	*input;
	char 		*used;
	size_t		i;

	shared = malloc(sizeof(t_oncreate));
	shared->section = 0;
	input = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' && s[i])
			i++;
		if (!s[i])
			break;
		used = new_element(&(s[i]), &input, shared);
		i += ft_strlen(used);
		free(used);
	}
	free(shared);
	return(input);
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
	i = 0;
	while (tmp[i])
	{
		//if (tmp[i] == '\"' || tmp[i] == '\'')
			//shared->inquotes = !shared->inquotes;
		check_quotes(tmp[i], shared);
		if (!shared->inquotes)
		{
			if (is_special_c(&(tmp[i]), totem, i, shared))
			{
				if (i)
					break;
				if (*(tmp + 1) == '<' || *(tmp + 1) == '>')
					tmp++;
				tmp++;
				while(tmp[i] == ' ' && tmp[i])
					tmp++;
			}
			else
			{
				if (tmp[i] == ' ')
					break;
				i++;
			}
		}
		else
			i++;
	}
	tmp[i] = 0;
	totem->content = ft_strdup((const char *)remove_quotes(tmp));
	totem->next = 0;
	ft_add_totem(input, totem);
	return (orig);
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
				totem->type= 'h';
			else
				totem->type= 'i';
		}
	}
	else if (*str == '>')
	{
		if (!i)
		{
			if (*(str + 1) == '>')
				totem->type= 'p';
			else
				totem->type= 'o';
		}
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

char	*remove_quotes(char *str)
{
	int	pos;
	char *mod;

	mod = ft_strdup(str);
	if (*mod == '\"' || *mod == '\'')
		mod++;
	pos = ft_strlen(mod) - 1;
	if (mod[pos] == '\"' || mod[pos] == '\'')
		mod[pos] = 0;
	return(mod);
}

void	check_quotes(char c, t_oncreate *shared)
{
	if (shared->inquotes)
	{
		if (c == shared->qtype)
			shared->inquotes = 0;
	}
	else if (c == '\"' || c == '\'')
	{
		shared->qtype = c;
		shared->inquotes = 1;
	}
	return ;
}