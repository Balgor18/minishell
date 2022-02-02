/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:10:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/02 12:12:09 by fcatinau         ###   ########.fr       */
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

static void	exec_wait_free(t_cmd *cmd)
{
	t_cmd	*cpy;

	while (cmd)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(cmd->pid, NULL, 0);
		init_signal(false);
		cpy = cmd;
		cmd = cmd->next;
		free_list(cpy->arg);
		free_list(cpy->red);
		free(cpy);
	}
}

void	exec_launch(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*start;

	start = cmd;
	tmp = cmd;
	while (cmd)
	{
		if (cmd->next)
			exec_pipe(&cmd);
		if (cmd->red)
			if (!exec_redir(cmd))
				dprintf(2, "Error in redir\n");
		if (!check_builtins(cmd))
			exec_fork(cmd, start);
		cmd = cmd->next;
	}
	exec_wait_free(start);
}
