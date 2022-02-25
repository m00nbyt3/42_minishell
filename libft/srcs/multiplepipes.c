/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplepipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:02 by agallipo          #+#    #+#             */
/*   Updated: 2022/02/22 19:45:30 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char **argv, char **env, int pipe)
{
	char	**flags;
	char	*command;

	if	(!*argv[pipe])
		ft_exit_process(1, argv[pipe]);
	flags = ft_split(argv[pipe], ' ');
	command = ft_env_path(env, argv[pipe], flags);
	if (execve(command, flags, env) < 0)
		ft_exit_process(2, argv[pipe]);
	ft_free_matrix(flags);
	exit(0);
}

void	ft_frst_child(int *fd, char **argv, char **env, int pipe)
{
	int	fd2;

	close(fd[READ_END]);

	fd2 = open(argv[pipe], O_RDONLY);
	dup2(fd2, STDIN_FILENO);  //cambias el stdin para leer el archivo
	close(fd2);

	dup2(fd[WRITE_END], STDOUT_FILENO);//extremo de escritura en vez de stdout
	close(fd[WRITE_END]);

	if (fd2 < 0)
		ft_exit_process(0, argv[pipe]);
	ft_execute(argv, env, pipe);
}

void 	ft_mid_child(int *fd, char **argv, char **env, int pipe)
{

	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);

	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);

	ft_execute(argv, env, pipe);
}

void	ft_lst_child(int *fd, char **argv, char **env, int pipe)
{
	int	fd2;

	//close(fd[WRITE_END); No se si ponerlo aquí
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);

	fd2 = open(argv[pipe + 1], O_CREATE | O_RDWR | O_TRUNC | O_APPEND, 0777);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);

	if (fd2 < 0)
		ft_exit_process(0, argv[pipe]);
	ft_execute(argv, env, pipe);
}

void	ft_pipes(int argc, char **argv, char **env)
{
	int	fd1[2];
	int	pid;
	int	pipes;
	int	i;

	pipe(fd1);
	pid = fork();
	pipes = argc - 3;
	
	if (pid == 0)
		ft_frst_child(fd1, argv, env);
	else
	{
		//mid_child y luego en ccle crear mids si los hay?
		i = 3;
		while (i < pipes)
		{
			pid = fork();
			if (pid == 0)
				ft_mid_child_pipe(fd1, i, argv, env);

			else
				wait(&pid);
			i++;
		}
		close(fd1[WRITE_END]);
		pid = fork();
		if (pid == 0)
			ft_bastard(fd1, argv, env, i);
		else
			close(fd1[READ_END]);
		wait(&pid);
	}
}
