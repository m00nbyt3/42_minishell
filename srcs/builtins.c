/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:14:54 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/28 11:11:54 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_builtins(t_totems *input, t_list **env);
void	ft_env(t_list **env);
void	ft_echo(t_totems *input, int section);
void	ft_cd(t_totems *input, int section, t_list **env);
void	ft_pwd(t_totems *input, int section);

void	set_fds(t_totems *input, int section);

int		ft_builtins(t_totems *input, t_list **env)
{
	void	*orig;
	int		ofdin;
	int		ofdout;
	int 	section;

	ofdin = dup(STDIN_FILENO);
	ofdout = dup(STDOUT_FILENO);
	orig = input;
	section = input->section;
	set_fds(input, section);
	while (input)
	{
		if (input->type == 'c')
		{
			if (ft_strcmp(input->content, "env"))
				ft_print_lst(*env);
			else if (ft_strcmp(input->content, "echo"))
				ft_echo(input, input->section);
			else if (ft_strcmp(input->content, "cd"))
				ft_cd(input, input->section, env);
			else if (ft_strcmp(input->content, "pwd"))
				ft_pwd(input, input->section);
			else if (ft_strcmp(input->content, "exit"))
				exit(0);
			else
			{
				input = orig;
				dup2(ofdin, STDIN_FILENO);
				close(ofdin);
				dup2(ofdout, STDOUT_FILENO);
				close(ofdout);
				return (0);
			}
			break ;
		}
		input = input->next;
	}
	input = orig;
	dup2(ofdin, STDIN_FILENO);
	close(ofdin);
	dup2(ofdout, STDOUT_FILENO);
	close(ofdout);
	return(1);
}

void	ft_echo(t_totems *input, int section)
{
	void	*orig;
	int		newline;
	int		imfirst;

	orig = input;
	newline = 1;
	imfirst = 1;
	while (input && input->section == section)
	{
		if (input->type == 'a' && imfirst)
		{
			printf("%s", input->content);
			imfirst = 0;
		}
		else if (input->type == 'a')
			printf(" %s", input->content);
		if (input->type == 'f')
			if (ft_strcmp(input->content, "n"))
				newline = 0;
		input = input->next;
	}
	if (newline)
		printf("\n");
	input = orig;
}

void	ft_cd(t_totems *input, int section, t_list **env)
{	
	char	*home;

	while (input && input->section == section)
	{
		if (input->type == 'a')
		{
			chdir(input->content);
			break ;
		}
		input = input->next;
	}
}

void	ft_pwd(t_totems *input, int section)
{
	char	*buf;
	
	buf = getcwd(0, 0);
	printf("%s\n", buf);
	free(buf);
}

void	set_fds(t_totems *input, int section)
{
	void	*orig;
	int		fd;

	orig = input;
	while (input)
	{
		if (input->type == 'i')
		{
			fd = open(input->content, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (input->type == 'o')
		{
			fd = open(input->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		input = input->next;
	}
	input = orig;
}