/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:32:09 by ycarro            #+#    #+#             */
/*   Updated: 2022/04/20 15:11:31 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fds(t_totems *input, int section);
char	*ft_srchlist_var(char *tofind, t_list **env);
char	*ft_vsrch_var(char *tofind, char **env);
void	ft_print_mtx(char **env);

void	set_fds(t_totems *input, int section)
{
	void	*orig;
	int		fd;

	orig = input;
	while (input)
	{
		if (input->type == 'i')
		{
			fd = open(input->content, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (input->type == 'o')
		{
			fd = open(input->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		input = input->next;
	}
	input = orig;
}

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
	int i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

