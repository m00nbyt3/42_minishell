/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:08:30 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/09 15:08:03 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_transformer *content, t_env *env);
void	find_variable(char	*str, int fd, int *i, t_env *env);
void	cutstr(char *str, char c);
void	exit_here(int sig);

void	here_doc(t_transformer *content, t_env *env)
{
	char	*str;
	int		i;
	int		quotes;

	set_origina_fd();
	str = malloc(sizeof(char *));
	content->fdin = open("/private/tmp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	quotes = 0;
	if (content->qtype == '\"' || content->qtype == '\'')
		quotes = 1;
	while (42)
	{
		signal(SIGINT, exit_here);
		str = readline(">");
		if (str == NULL)
			exit_here(0);
		if (ft_strcmp(str, content->heredoc))
			break ;
		i = 0;
		while (str[i])
		{
			if (str[i] == '$' && quotes == 0)
				find_variable(str, content->fdin, &i, env);
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

void	exit_here(int sig)
{
	ft_putstr_fd("\n", 2);
	exit (0);
}

void	find_variable(char	*str, int fd, int *i, t_env *env)
{
	char	*aux;
	char	*orig;

	orig = ft_strdup(&str[*i]);
	aux = orig + 1;
	cutstr(aux, ' ');
	aux = get_my_env(aux, env->array);
	ft_putstr_fd(aux, fd);
	free(orig);
	(*i)++;
	if (str[(*i)] == ' ' || str[(*i)] == 0)
	{
		write(fd, "$", 1);
		return ;
	}
	while (str[*i] != '\0')
	{
		if (str[*i] == ' ' || str[*i] == '$'|| str[*i] == '\''|| str[*i] == '\"')
			break ;
		(*i)++;
	}
}

void	cutstr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c && str[i] != '$'&& str[i] != '\''&& str[i] != '\"')
		i++;
	str[i] = '\0';
}
