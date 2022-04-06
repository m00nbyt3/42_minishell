/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:08:30 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/06 16:33:52 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_transformer *content);
void	find_variable(char	*str, int fd, int *i);
//cuando el transormer este ok, pasalo como parametro y edita el fdin
void	here_doc(t_transformer *content)
{
	char	*str;
	int		fd;
	int		i;
	int		jump;

	str = malloc(sizeof(char *));
	fd = open("temp.txt", O_CREAT | O_WRONLY);
	//dup2(fd, STDOUT_FILENO);
	jump = 0;
	while (42)
	{
		str = readline(">");
		if (ft_strcmp(str, content->heredoc))
			break ;
		//if (jump != 0)
			write(fd, "\n", 1);
		jump++;
		i = 0;
		while (str[i])
		{
			if (str[i] == '$')
				find_variable(str, fd, &i);
			else
				write(fd, &str[i], 1);
			i++;
		}
	}
	close(fd);
	content->fdin = open("temp.txt", O_RDONLY);
	dup2(content->fdin, STDIN_FILENO);
	close(content->fdin);
	 //No se cierra aqui porque el proceso ya lo hace con el dup
	//exit(0);
}

void	find_variable(char	*str, int fd, int *i)
{
	char	*aux;

	aux = ft_strchr(str, '$');
	*aux++;
	aux = getenv(aux);
	while (str[*i] != ' ' || str[*i] != '\0')
	{
		*i++;
	}
	ft_putstr_fd(aux, fd);
}
