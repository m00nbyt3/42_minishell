/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:36:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/03/04 17:36:43 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_totems	*sp_split(char *s);
char		*new_element(char *s, t_totems **input);
int			is_special_c(char *str, t_totems *totem, int i);
char		*remove_quotes(char *str);

t_totems	*sp_split(char *s)
{
	t_totems	*input;
	char 		*used;
	size_t		i;

	input = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' && s[i])
			i++;
		used = new_element(&(s[i]), &input);
		i += ft_strlen(used);
		free(used);
	}
	return(input);
}

char	*new_element(char *s, t_totems **input)
{
	t_totems	*totem;
	char		*tmp;
	char		*orig;
	int			i;
	int			inquotes;

	totem = malloc(sizeof(t_totems));
	if (!totem)
		return (0);
	tmp = ft_strdup((const char *)s);
	inquotes = 0;
	totem->section = 0;
	totem->type = 0;
	orig = tmp;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			inquotes = !inquotes;
		if (!inquotes)
		{
			if (is_special_c(&(tmp[i]), totem, i))
			{
				if (i)
					break;
				else
				{
					tmp++;
					while(tmp[i] == ' ' && tmp[i])
						tmp++;
				}
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

int	is_special_c(char *str, t_totems *totem, int i)
{
	while (*str == ' ' && *str)
		str++;
	if (*str == '<')
	{
		if (!i)
		{
			if (*str + 1 == '<')
				totem->type= 'u';
			else
				totem->type= 'i';
		}
	}
	else if (*str == '>')
	{
		if (!i)
		{
			if (*str + 1 == '>')
				totem->type= 'p';
			else
				totem->type= 'o';
		}
	}
	else if (*str == '|')
	{
		if (!i)
			totem->section++;
	}
	else
	{
		if (!totem->type)
			totem->type = 'a';
		return (0);
	}
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