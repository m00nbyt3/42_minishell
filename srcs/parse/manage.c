/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:32:14 by ycarro            #+#    #+#             */
/*   Updated: 2022/05/15 13:35:27 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_transformer	*init_transformer(t_transformer *runner);

t_transformer	*init_transformer(t_transformer *runner)
{
	runner = malloc(sizeof(t_transformer));
	runner->cmd = 0;
	runner->fdin = -2;
	runner->fdout = -2;
	runner->heredoc = 0;
	runner->append = 0;
	return (runner);
}
