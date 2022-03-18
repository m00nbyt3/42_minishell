/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:02 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/18 17:47:46 by ycarro           ###   ########.fr       */
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
		//ft_exit_process(2, smth->cmd);
		write(1,0,1);
	ft_free_matrix(smth->flags);
	exit(0);
}

void	ft_frst_child_pipe(t_transformer *smth, char **env, int *fd)
{
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

void 	ft_mid_child_pipe(t_transformer *smth, char **env, int *fd1, int *fd2)
{

	dup2(fd1[READ_END], STDIN_FILENO);
	close(fd1[READ_END]);

	dup2(fd2[WRITE_END], STDOUT_FILENO);
	close(fd2[WRITE_END]);

	ft_execute(smth, env);
}

void	ft_bastard(t_transformer *smth, char **env, int *fd1)
{

	//close(fd[WRITE_END); No se si ponerlo aquí
	dup2(fd1[READ_END], STDIN_FILENO);
	close(fd1[READ_END]);
	
	if (smth->fdout != 1)
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}
	ft_execute(smth, env);
}

void	ft_pipes(t_transformer **smtha, char **env, t_totems *input, t_list *envlist)
{
	int	**fd1;
	int	pid;
	t_transformer *smth;
	int	i;

	i = 0;
	fd1 = malloc(5 * sizeof(int *));
	*fd1 = malloc(2 * sizeof(int));
	smth = *smtha;
	pipe(*fd1);
	pid = fork();
	if (pid == 0)
	{
		printf("here1\n");
		ft_frst_child_pipe(smth, env, fd1[0]);
	}	
	else if(!ft_builtins(input, &envlist) && smth->next)
	{
		smth = smth->next;
		//mid_child y luego en ccle crear mids si los hay?
		while (smth && smth->next)
		{
			printf("here3\n");
			i++;
			pipe(fd1[1]);
			pid = fork();
			if (pid == 0)
				ft_mid_child_pipe(smth, env, fd1[i], fd1[i + 1]);
			else
				wait(&pid);
			smth = smth->next;
			break;
		}
		if (smth)
		{
			printf("here2\n");
			//smth = smth->next;
			close(fd1[i][WRITE_END]);
			pid = fork();
			if (pid == 0)
				ft_bastard(smth, env, fd1[i]);
			else
				close(fd1[i][READ_END]);
		}
		wait(&pid);
	}
}


