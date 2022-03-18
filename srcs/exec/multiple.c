/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:02 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/18 12:39:38 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_transformer *smth, char **env)
{
	char	*command;

	if	(!*smth->cmd)
		ft_exit_process(1, smth->cmd);
	command = ft_env_path(env, smth->cmd, smth->flags);
	if (execve(command, smth->flags, env) < 0)
		ft_exit_process(2, smth->cmd);
	ft_free_matrix(smth->flags);
	exit(0);
}

void	ft_frst_child_pipe(t_transformer *smth, char **env, int *fd)
{
	int	fd2;

	close(fd[READ_END]);
	if (smth->fdin != 0)
	{
		dup2(smth->fdin, STDIN_FILENO);  //cambias el stdin para leer el archivo
		close(smth->fdin);
	}
	if (smth->fdout != 1)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);//extremo de escritura en vez de stdout
		close(fd[WRITE_END]);
	}
/********antes******
	fd2 = open(argv[pipe], O_RDONLY);
	dup2(fd2, STDIN_FILENO);  //cambias el stdin para leer el archivo
	close(fd2);

	dup2(fd[WRITE_END], STDOUT_FILENO);//extremo de escritura en vez de stdout
	close(fd[WRITE_END]);
*/
	ft_execute(smth, env);
}

void 	ft_mid_child_pipe(t_transformer *smth, char **env, int *fd)
{

	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);

	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);

	ft_execute(smth, env);
}

void	ft_bastard(t_transformer *smth, char **env, int *fd)
{

	//close(fd[WRITE_END); No se si ponerlo aquí
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	
	if (smth->fdout != 1)
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	ft_execute(smth, env);
}

void	ft_pipes(t_transformer **smtha, char **env)
{
	int	fd1[2];
	int	pid;
	t_transformer *smth;

	smth = *smtha;
	smth->fdin = 0;
	smth->fdout = 1;
	pipe(fd1);
	pid = fork();
	if (pid == 0)
	{
		ft_frst_child_pipe(smth, env, fd1);
		smth = smth->next;
	}
	else
	{
		//mid_child y luego en ccle crear mids si los hay?
		while (smth && smth->next)
		{
			pipe(fd1);
			pid = fork();
			if (pid == 0)
				ft_mid_child_pipe(smth, env, fd1);
			else
				wait(&pid);
			smth = smth->next;
		}
		if (smth)
		{
			close(fd1[WRITE_END]);
			pipe(fd1);
			pid = fork();
			if (pid == 0)
				ft_bastard(smth, env, fd1);
			else
				close(fd1[READ_END]);
		}
		wait(&pid);
	}
}


