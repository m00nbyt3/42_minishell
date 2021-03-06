/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:16:08 by agallipo          #+#    #+#             */
/*   Updated: 2022/05/15 16:22:55 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_directory(char **flags);
char	*ft_env_path(char **env, char *argv, char **flags);
char	**ft_path_split(char **env);

int	ft_check_directory(char **flags)
{
	int	fd;

	fd = open(flags[0], O_DIRECTORY);
	if (fd != -1)
	{
		write(2, "W4V3shell# ", 11);
		perror(" ");
	}
	return (1);
}

char	*ft_env_path(char **env, char *argv, char **flags)
{
	char	**path;
	char	*cmd;
	int		i;

	if (access(argv, X_OK) == 0)
		return (argv);
	path = ft_path_split(env);
	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		cmd = strdup(path[i]);
		ft_strlcat(cmd, "/", ft_strlen(cmd) + 2);
		ft_strlcat(cmd, flags[0], ft_strlen(cmd) + ft_strlen(flags[0]) + 1);
		if (access(cmd, X_OK | R_OK) == 0)
			return (cmd);
		i++;
	}
	free(cmd);
	ft_free_matrix(path);
	return (0);
}

char	**ft_path_split(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i], ':');
			return (path);
		}
		i++;
	}
	return (0);
}
