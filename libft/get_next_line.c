/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 19:26:42 by agallipo          #+#    #+#             */
/*   Updated: 2021/12/01 12:57:48 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_readln(t_var *variable, char **line, int fd)
{
	while (variable->rd > 0)
	{
		variable->chk = ft_strchr(variable->buff, '\n');
		variable->aux = ft_strjoin(*line, variable->buff);
		free(*line);
		*line = ft_strdup(variable->aux);
		free(variable->aux);
		if (variable->chk != NULL)
			break ;
		variable->rd = read(fd, variable->buff, BUFFER_SIZE);
		variable->buff[variable->rd] = '\0';
	}
	return (*line);
}

static char	*ft_putnl(t_var *variable, char **line)
{
	variable->len = 0;
	while (line[0][variable->len] != '\n' && line[0][variable->len] != '\0')
		variable->len++;
	variable->aux = ft_substr(*line, 0, (variable->len + 1));
	free(*line);
	*line = NULL;
	*line = ft_strdup(variable->temp);
	free(variable->temp);
	variable->temp = NULL;
	return (variable->aux);
}

static char	*ft_end(t_var *variable, char **line)
{
	variable->aux = ft_strdup(*line);
	free(*line);
	*line = NULL;
	return (variable->aux);
}

static char	*ft_emptyln(char **line)
{
	free(*line);
	*line = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*line;
	t_var		variable;

	variable.temp = NULL;
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, variable.buff, 0) == -1)
		return (NULL);
	variable.rd = read(fd, variable.buff, BUFFER_SIZE);
	if (variable.rd == -1 && !line)
		return (NULL);
	variable.buff[variable.rd] = '\0';
	if (!line)
		line = ft_strdup("");
	line = ft_readln(&variable, &line, fd);
	variable.chk = ft_strchr(line, '\n');
	if (variable.chk && variable.chk[0] != '\0')
		variable.temp = ft_strdup(variable.chk + 1);
	if (line == NULL || line[0] == '\0')
		return (ft_emptyln(&line));
	if (variable.temp)
		return (ft_putnl(&variable, &line));
	else
		return (ft_end(&variable, &line));
	return (NULL);
}
