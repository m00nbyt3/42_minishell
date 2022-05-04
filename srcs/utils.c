/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:58:28 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/29 18:20:57 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*store_env_in_list(char **environ);
void	run_cmd(char *complete, t_env *env);
t_env	*store_environ();
void	sort_mtx(char **mtx);
t_env	*basic_env();

t_env	*basic_env()
{
	t_env			*env;

	env = malloc(sizeof(t_env));

	env->array = malloc(sizeof(char *) * 3);
	env->array[0] = ft_strdup(ft_strjoin("PWD=", getcwd(0,0)));
	env->array[1] = ft_strdup(ft_strjoin("SHLVL=", ft_itoa(g_util.shlvl)));
	env->array[2] = 0;
	env->export = ft_mtxdup(env->array);
	env->list = store_env_in_list(env->array);
	return (env);
}
void	shell_level(t_env *env)
{
	int		i;
	//char	*aux;

	i = 0;
	while (env->array[i])
	{
		//dprintf(2, "AHHHH%s\n", env->array[i - 1]);
		if (ft_strncmp("SHLVL=", env->array[i], 6) == 0)
		{
			g_util.shlvl++;
			break ;
		}
		i++;
	}
	env->array[i] = ft_strdup(ft_strjoin("SHLVL=", ft_itoa(g_util.shlvl)));
}

t_env	*store_environ()
{
	t_env			*env;
	extern char		**environ;

	if (!(*environ))
		return (basic_env());
	env = malloc(sizeof(t_env));
	env->export = ft_mtxdup(environ);
	env->array = environ;
	env->list = store_env_in_list(environ);
	//shell_level(env);
	return (env);
}
t_list	*store_env_in_list(char **environ)
{
	t_list	*env;

	env = NULL;
	while (*environ)
	{
		ft_lstadd_back(&env, ft_lstnew(*environ));
		environ++;
	}
	return (env);
}

void	run_cmd(char *complete, t_env *env)
{
	t_transformer	*content;

	content->flags = ft_split(complete, ' ');
	content->cmd = *content->flags;
	content->fdin = -2;
	content->fdout = -2;
	content->heredoc = 0;
	content->append = 0;
	single_cmd(0, content, env);
}

void	sort_mtx(char **mtx)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while(mtx[i])
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
