/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:12:49 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/15 15:14:47 by ycarro           ###   ########.fr       */
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
				return ("$");
			if (orig[i + 1] == '?' && (orig[i + 2] == ' ' || !orig[i + 2]))
				return (ft_itoa(g_util.exit_value));
			aux = ft_strdup(orig + (i + 1));
			if (!expand_dollar(&aux, env, &ret))
				return (0);
		}
		i++;
	}
	return (ret);
}

int	expand_dollar(char **aux, t_env *env, char **ret)
{
	cutstr(*aux, ' ');
	*aux = get_my_env(*aux, env->array);
	if (!(*aux))
		return (0);
	*ret = ft_strjoin(*ret, *aux);
	return (1);
}
