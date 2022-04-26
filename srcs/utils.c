/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:58:28 by agallipo          #+#    #+#             */
/*   Updated: 2022/04/26 16:03:22 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*store_env_in_list(char **environ);
void	run_cmd(char *complete, t_env *env);
t_env	*store_environ();

t_env	*store_environ()
{
	t_env			*env;
	extern char		**environ;

	env = malloc(sizeof(t_env));
	env->array = environ;
	env->list = store_env_in_list(environ);
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
