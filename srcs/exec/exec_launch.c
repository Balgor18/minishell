/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:10:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/24 17:54:29 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_pipe(t_cmd **cmd)
{
	int	pip[FD_MAX];

	if (pipe(pip) < 0)
		return ;
	(*cmd)->fd[OUT] = pip[IN];
	(*cmd)->next->fd[IN] = pip[OUT];
}

void	exec_launch(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		if (cmd->next)
			exec_pipe(&cmd);
		exec_redir(cmd);
		cmd = cmd->next;
	}
}
