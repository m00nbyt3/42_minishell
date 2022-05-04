/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:32:09 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/04 12:23:02 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_srchlist_var(char *tofind, t_list **env);
char	*ft_vsrch_var(char *tofind, char **env);
void	ft_print_mtx(char **env);
void	ft_print_export(char **env);

char	*ft_srchlist_var(char *tofind, t_list **env)
{
	int		len;
	char	*tmp;
	char	*result;
	t_list	*list;

	list = *env;
	len = ft_strlen(tofind);
	result = 0;
	while (list->content)
	{
		if (!ft_strncmp(tofind, list->content, len))
		{
			tmp = ft_strdup(list->content);
			break ;
		}
		list = list->next;
	}
	if (tmp)
	{
		result = ft_strdup(tmp + (len + 1));
		free(tmp);
	}
	return (result);
}

char	*ft_vsrch_var(char *tofind, char **env)
{
	int		len;
	char	*tmp;
	char	*result;
	void	*orig;

	orig = env;
	len = ft_strlen(tofind);
	result = 0;
	while (*env)
	{
		if (!ft_strncmp(tofind, *env, len))
		{
			tmp = ft_strdup(*env);
			break ;
		}
		env++;
	}
	if (tmp)
	{
		result = ft_strdup(tmp + (len + 1));
		free(tmp);
	}
	env = orig;
	return (result);
}

void	ft_print_mtx(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	ft_print_export(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
}
