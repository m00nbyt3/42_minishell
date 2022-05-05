/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:58:28 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/05 14:03:53 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*store_env_in_list(char **environ);
void	run_cmd(char *complete, t_env *env);
t_env	*store_environ();
void	sort_mtx(char **mtx);
char	*fvck_quotes(char *vector, char qtype);
t_env	*basic_env();
void	shell_level(t_env *env);
char	*set_quotes(char *str);
char	*chr2str(char toadd, char *str);

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
	printf("hjey\n");
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

char	*fvck_quotes(char *vector, char qtype)
{
	int 	count;
	char	*orig;
	
	orig = vector;
	count = 0;
	if (qtype == '\'')
		count += 1;
	if (qtype == '\"')
			count += 2;
	printf("First: %s\n", vector);
	while (*vector == '\'' || *vector == '\"')
	{
		if (*vector == '\'')
			count += 1;
		if (*vector == '\"')
			count += 2;
		vector++;
	}
	printf("%d", count);
	if (!(count % 2))
	{
		ft_strtrim(vector, "\'");
		printf("hey%s\n", vector);
		return (getdollars(vector));
	}
	return (orig);
}

char	*set_quotes(char *str)
{
	int		i;
	int		squote;
	int		dquote;
	char	*tmp;

	tmp = 0;
	squote = 0;
	dquote = 0;
	i = 0;
	while(str[i])
	{
		printf("Char %c ->", str[i]);
		if (squote == 2 || dquote == 2)
			{
				squote = 0;
				dquote = 0;
			}
		if (str[i] == '\'' && dquote != 1)
			squote++;
		else if (str[i] == '\"' && squote != 1)
			dquote++;
		else if (squote || dquote)
		{
			//else
				tmp = chr2str(str[i], tmp);
		}
		printf("NOT SAVED (%c)\n", str[i]);
		printf("STATUS: s->%d  d->%d\n", squote, dquote);
		i++;
	}
	if (tmp)
		return (tmp);
	else
		return (str);
}

char	*chr2str(char toadd, char *str)
{
	char	*new;
	int		i;

	printf("SAVED (%c)\n", toadd);
	i = 0;
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
		free(str);
	}
	new[i] = toadd;
	new[i + 1] = 0;
	return(new);
}
