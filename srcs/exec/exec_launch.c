/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:10:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/07 19:12:41 by fcatinau         ###   ########.fr       */
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

static void	close_fd(t_cmd *cmd)
{
	if (cmd->fd[IN] != STDIN_FILENO)
		close(cmd->fd[IN]);
	if (cmd->fd[OUT] != STDOUT_FILENO)
		close(cmd->fd[OUT]);
}

static void	exec_child_ret(int pid)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_error = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		g_error = 128 + WTERMSIG(wstatus);
		error_sig();
		write(STDOUT_FILENO, "\n", 1);
	}
}

static void	exec_wait_free(t_cmd *cmd)
{
	t_cmd	*cpy;

	while (cmd)
	{
		signal(SIGINT, SIG_IGN);
		if (cmd->pid > 0)
			exec_child_ret(cmd->pid);
		init_signal(false);
		cpy = cmd;
		cmd = cmd->next;
		if (!cpy->arg)
			close_fd(cpy);
		free_list(cpy->arg);
		free_list(cpy->red);
		free(cpy);
	}
}

void	exec_launch(t_cmd *cmd)
{
	t_cmd	*start;
	bool	error_found;
	int		ret;

	start = cmd;
	while (cmd)
	{
		error_found = false;
		if (cmd->next)
			exec_pipe(&cmd);
		if (cmd->red)
		{
			ret = exec_redir(cmd);
			if (ret == -1)
				break ;
			if (!ret)
				error_found = true;
		}
		if (!error_found && cmd->arg && !check_builtins(cmd->arg->word, cmd))
			exec_fork(cmd, start);
		close_fd(cmd);
		cmd = cmd->next;
	}
	exec_wait_free(start);
}
