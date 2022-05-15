/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:32:09 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/15 16:14:38 by ycarro           ###   ########.fr       */
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
	tmp = 0;
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
	tmp = 0;
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
		result = ft_strdup(tmp + (len));
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
	{
		ft_putstr_fd(env[i], 1);
		write(1, "\n", 1);
	}
}

void	ft_print_export(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
}
