/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:12:49 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/16 15:25:12 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getdollars(char *orig, t_env *env);
int		expand_dollar(char **aux, t_env *env, char **ret);

char	*getdollars(char *orig, t_env *env)
{
	char	*aux;
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(sizeof(char *), 1);
	while (orig[i])
	{
		if (orig[i] == '$')
		{
			if (orig[i + 1] == ' ' || !orig[i + 1])
			{
				free(ret);
				return ("$");
			}
			if (orig[i + 1] == '?' && (orig[i + 2] == ' ' || !orig[i + 2]))
			{
				free(ret);
				return (ft_itoa(g_util->exit_value));
			}
			aux = ft_strdup(orig + (i + 1));
			if (!expand_dollar(&aux, env, &ret))
				return (0);
		}
		i++;
	}
	free(orig);
	return (ret);
}

int	expand_dollar(char **aux, t_env *env, char **ret)
{
	void	*orig;

	orig = *aux;
	cutstr(*aux, ' ');
	free(orig);
	*aux = get_my_env(*aux, env->array);
	if (!(*aux))
		return (0);
	free(*ret);
	*ret = ft_strjoin(*ret, *aux);
	free(*aux);
	return (1);
}
