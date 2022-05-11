/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:58:28 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/11 18:45:44 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*store_env_in_list(char **environ);
void	run_cmd(char *complete, t_env *env);
t_env	*store_environ(void);
void	sort_mtx(char **mtx);
char	*fvck_quotes(char *vector, char qtype, t_env *env);
t_env	*basic_env(void);
char	**shell_level(char **env);
char	*set_quotes(char *str, t_oncreate *shared);
char	*inside_quote(char *str, char **tmp, t_oncreate *shared, int *force);
char	*chr2str(char toadd, char *str, int *force);
int		checkargs(t_transformer *runner, t_env *env);
char	*get_my_env(char *name, char **env);

char	*get_my_env(char *name, char **env)
{
	int		i;
	int		len;
	char	*expanded;

	len = ft_strlen(name);
	i = 0;
	expanded = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0)
		{
			expanded = ft_strdup(env[i] + (len + 1));
			break ;
		}
		i++;
	}
	return (expanded);
}

t_env	*basic_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->array = ft_calloc(4, sizeof(char *));
	env->array[0] = ft_strdup(ft_strjoin("PWD=", getcwd(0, 0)));
	shell_level(env->array);
	env->array[2] = ft_strdup("_=/usr/bin/env");
	env->array[3] = 0;
	env->export = ft_mtxdup(env->array);
	env->list = store_env_in_list(env->array);
	return (env);
}

char	**shell_level(char **env)
{
	int		i;
	int		lvl;
	char	*aux;
	int		found;

	i = 0;
	lvl = 1;
	found = 0;
	while (env[i])
	{
		if (ft_strncmp("SHLVL=", env[i], 6) == 0)
		{	
			found++;
			aux = env[i] + 6;
			lvl = ft_atoi(aux) + 1;
			if (lvl <= 0)
				lvl = 1;
			break ;
		}
		i++;
	}
	if (!found)
		env = ft_env_add(ft_strjoin("SHLVL=", ft_itoa(lvl)), env);
	else
		env[i] = ft_strdup(ft_strjoin("SHLVL=", ft_itoa(lvl)));
	return(env);
}

t_env	*store_environ(void)
{
	t_env			*env;
	extern char		**environ;

	if (!(*environ))
		return (basic_env());
	env = malloc(sizeof(t_env));
	env->export = ft_mtxdup(environ);
	env->array = ft_mtxdup(environ);
	env->array = shell_level(env->array);
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

char	*fvck_quotes(char *vector, char qtype, t_env *env)
{
	int		count;
	char	*orig;

	orig = vector;
	count = 0;
	if (qtype == '\'')
		count += 1;
	if (qtype == '\"')
			count += 2;
	while (*vector == '\'' || *vector == '\"')
	{
		if (*vector == '\'')
			count += 1;
		if (*vector == '\"')
			count += 2;
		vector++;
	}
	if (!(count % 2))
	{
		ft_strtrim(vector, "\'");
		return (getdollars(vector, env));
	}
	return (orig);
}

char	*set_quotes(char *str, t_oncreate *shared)
{
	char	*tmp;
	int		force;

	tmp = 0;
	force = 0;
	while(*str)
	{
		if (*str == '\'' || *str == '\"')
			str = inside_quote(str, &tmp, shared, &force);
		else
		{
			shared->qtype = 0;
			tmp = chr2str(*str, tmp, &force);
		}
		str++;
	}
	if (tmp)
		return (tmp);
	else
		return (ft_strdup(str));
}

char	*inside_quote(char *str, char **tmp, t_oncreate *shared, int *force)
{
	char qtype = *str;

	str++;
	if (!(*force))
			shared->qtype = qtype;
	while(*str != qtype)
	{
		*tmp = chr2str(*str, *tmp, force);
		str++;
	}
	return (str);
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
	return(new);
}

int		checkargs(t_transformer *runner, t_env *env)
{
	void	*orig;
	int		pid;

	orig =  runner;
	while (runner)
	{
		if (runner->heredoc)
		{
			pid = fork();
			if (!pid)
				here_doc(runner, env);
			else
				wait(&pid);
		}
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
