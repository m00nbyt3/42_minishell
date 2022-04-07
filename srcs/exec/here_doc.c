/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:08:30 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/07 14:52:31 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_transformer *content);
void	find_variable(char	*str, int fd, int *i);
//cuando el transormer este ok, pasalo como parametro y edita el fdin
void	here_doc(t_transformer *content)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char *));
	content->fdin = open("/private/tmp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (42)
	{
		str = readline(">");
		if (ft_strcmp(str, content->heredoc))
			break ;
		i = 0;
		while (str[i])
		{
			if (str[i] == '$')
				find_variable(str, content->fdin, &i);
			else
				write(content->fdin, &str[i], 1);
			i++;
		}
		write(content->fdin, "\n", 1);
	}
	close(content->fdin);
	content->fdin = open("/private/tmp/tmp", O_RDONLY);
	dup2(content->fdin, STDIN_FILENO);
	close(content->fdin);
}

void	find_variable(char	*str, int fd, int *i)
{
	char	*aux;

	aux = ft_strchr(str, '$');
	aux++;
	aux = getenv(aux);
	while (str[*i] != ' ' || str[*i] != '\0')
	{
		(*i)++;
	}
	ft_putstr_fd(aux, fd);
}
