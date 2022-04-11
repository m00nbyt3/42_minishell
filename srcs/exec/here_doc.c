/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:08:30 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/11 16:29:10 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_transformer *content);
void	find_variable(char	*str, int fd, int *i);
int		if_quotes(char *heredoc); 
void	cutstr(char *str, char c);
//cuando el transormer este ok, pasalo como parametro y edita el fdin
void	here_doc(t_transformer *content)
{
	char	*str;
	int		i;
	int		quotes;

	str = malloc(sizeof(char *));
	content->fdin = open("/private/tmp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	quotes = if_quotes(content->heredoc);
	while (42)
	{
		str = readline(">");
		if (ft_strcmp(str, content->heredoc))
			break ;
		i = 0;
		while (str[i])
		{
			if (str[i] == '$' && quotes == 0)
				find_variable(str, content->fdin, &i);
			else
			{
				write(content->fdin, &str[i], 1);
				i++;
			}
		}
		write(content->fdin, "\n", 1);
	}
	close(content->fdin);
	content->fdin = open("/private/tmp/tmp", O_RDONLY);
	dup2(content->fdin, STDIN_FILENO);
	close(content->fdin);
}

int	if_quotes(char *heredoc)
{
	int	len;

	dprintf(2, "here: %s", heredoc);
	len = ft_strlen(heredoc) - 1;
	if (heredoc[0] == '\"' && heredoc[len] == '\"')
	{
		heredoc++;
		heredoc[len] = '\0';
		return 1;
	}
	return 0;
}
void	find_variable(char	*str, int fd, int *i)
{
	char	*aux;
	char	*orig;

	orig = ft_strdup(&str[*i]);
	aux = orig + 1;
	cutstr(aux, ' ');
	aux = getenv(aux);
	ft_putstr_fd(aux, fd);
	free(orig);
	while (str[*i] != '\0')
	{
		if (str[*i] == ' ')
			break ;
		(*i)++;
	}
}

void	cutstr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	str[i] = '\0';
}
