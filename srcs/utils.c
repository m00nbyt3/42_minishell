/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:58:28 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/15 15:21:41 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_mtx(char **mtx);
char	*chr2str(char toadd, char *str, int *force);
int		checkargs(t_transformer *runner, t_env *env);
void	set_origina_fd(void);

void	sort_mtx(char **mtx)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (mtx[i])
	{
		j = i + 1;
		while (mtx[j])
		{
			if (ft_strncmp(mtx[i], mtx[j], ft_strlen(mtx[i])) > 0)
			{
				aux = mtx[i];
				mtx[i] = mtx[j];
				mtx[j] = aux;
			}
			j++;
		}
		i++;
	}
	ft_print_export(mtx);
}

char	*chr2str(char toadd, char *str, int *force)
{
	char	*new;
	int		i;

	i = 0;
	if (toadd == '$')
		*force = 1;
	if (!str)
		new = malloc(2 * sizeof(char));
	else
	{
		new = malloc((ft_strlen(str) + 2) * sizeof(char));
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
		if (force)
			free(str);
	}
	new[i] = toadd;
	new[i + 1] = 0;
	return (new);
}

int	checkargs(t_transformer *runner, t_env *env)
{
	void	*orig;

	orig = runner;
	while (runner)
	{
		if (runner->heredoc)
			execute_heredoc(runner, env);
		if (!(runner->cmd))
		{
			if (!runner->heredoc && runner->fdout == -2)
			{
				write(2, "W4V3shell: command not found\n", 29);
				g_util.exit_value = 127;
			}
			return (0);
		}
		runner = runner->next;
	}
	runner = orig;
	return (1);
}

void	set_origina_fd(void)
{
	dup2(g_util.ofdin, STDIN_FILENO);
	close(g_util.ofdin);
	dup2(g_util.ofdout, STDOUT_FILENO);
	close(g_util.ofdout);
}
