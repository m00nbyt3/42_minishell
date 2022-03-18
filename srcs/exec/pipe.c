/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:10:30 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/18 12:17:11 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *error, char *arg)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(arg, 2);
	write(2, "\n", 1);
}

void	ft_exit_process(int condition, char *argv)
{
	if (condition == 0)
	{
		ft_print_error("pipex: file error: ", argv);
		exit (0);
	}
	if (condition == 1)
	{
		ft_print_error("pipex: command not found:", "");
		exit (0);
	}
	if (condition == 2)
	{
		ft_print_error("pipex: command not found: ", argv);
		exit (0);
	}
}

void	ft_frst_child(int *fd, char **argv, char **env)
{
	char	**flags;
	char	*command;
	int		fd2;

	close(fd[READ_END]);
	fd2 = open(argv[1], O_RDONLY);
	dup2(fd2, STDIN_FILENO);
	close(fd2);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	if (fd2 < 0)
		ft_exit_process(0, argv[1]);
	if (!*argv[2])
		ft_exit_process(1, argv[1]);
	flags = ft_split(argv[2], ' ');
	command = ft_env_path(env, argv[2], flags);
	if (execve(command, flags, env) < 0)
		ft_exit_process(2, argv[2]);
	ft_free_matrix(flags);
	exit (0);
}

void	ft_bastards(int *fd, char **argv, char **env)
{
	char	**flags;
	char	*command;
	int		fd2;

	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0777);
	if (fd2 < 0)
		ft_exit_process(0, argv[4]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	if (!*argv[3])
		ft_exit_process(1, argv[4]);
	flags = ft_split(argv[3], ' ');
	command = ft_env_path(env, argv[3], flags);
	if (execve(command, flags, env) < 0)
		ft_exit_process(2, argv[3]);
	ft_free_matrix(flags);
	exit (0);
}

int	ft_pipe(char **argv, char **env)
{
	int	fd1[2];
	int	pid;

	pipe(fd1);
	pid = fork();
	if (pid == 0)
		ft_frst_child(fd1, argv, env);
	else
	{
		close(fd1[WRITE_END]);
		pid = fork();
		if (pid == 0)
			ft_bastards(fd1, argv, env);
		else
			close(fd1[READ_END]);
		wait(&pid);
		wait(&pid);
	}
	return (0);
}
