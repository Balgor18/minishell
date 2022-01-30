/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:10:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/29 23:18:18 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_pipe(t_cmd **cmd)
{
	int	pip[FD_MAX];

	if (pipe(pip) < 0)
		return ;
	(*cmd)->fd[OUT] = pip[OUT];
	(*cmd)->next->fd[IN] = pip[IN];
}

void	exec_launch(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		if (cmd->next)
			exec_pipe(&cmd);
		if (cmd->red)
			if (!exec_redir(cmd))
				dprintf(2, "Error in redir\n");
		if (check_builtins(cmd))
		{
			tmp = cmd;
			cmd = cmd->next;
			tmp->next = NULL;
			free_cmd(tmp);
		}
		else
			exec_fork(&cmd);
	}
}
