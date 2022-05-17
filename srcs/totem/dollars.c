/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:12:49 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/17 13:13:38 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*getdollars(char *orig, t_env *env);
int			expand_dollar(char **aux, t_env *env, char **ret);
static char	*ret_free(char *tofree, char *str, char *extra);

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
				return (ret_free(ret, ft_strdup("$"), orig));
			if (orig[i + 1] == '?' && (orig[i + 2] == ' ' || !orig[i + 2]))
				return (ret_free(ret, ft_itoa(g_util->exit_value), orig));
			aux = ft_strdup(orig + (i + 1));
			if (!expand_dollar(&aux, env, &ret))
			{
				free(ret);
				free(aux);
				free(orig);
				return (0);
			}
		}
		i++;
	}
	free(orig);
	return (ret);
}

static char	*ret_free(char *tofree, char *str, char *extra)
{
	free(tofree);
	free(extra);
	return (str);
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
