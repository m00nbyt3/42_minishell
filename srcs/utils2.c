/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:43:16 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/16 15:06:52 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cutstr(char *str, char c);
void	allocate_fds(t_tools *tools);
void	close_all_fds(t_tools *tools);

void	cutstr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c && str[i] != '$' && str[i] != '\'' \
	&& str[i] != '\"')
		i++;
	str[i] = '\0';
}

void	allocate_fds(t_tools *tools)
{
	int	i;

	i = 0;
	tools->fd = malloc(tools->npipes * sizeof(int *));
	while (i < tools->npipes)
	{
		tools->fd[i] = malloc(2 * sizeof(int));
		tools->fd[i][0] = -42;
		tools->fd[i][1] = -42;
		i++;
	}
}

void	close_all_fds(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->npipes)
	{
		close(tools->fd[i][0]);
		close(tools->fd[i][1]);
		free(tools->fd[i]);
		i++;
	}
	free(tools->fd);
}
