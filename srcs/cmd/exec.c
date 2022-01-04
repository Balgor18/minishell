/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:26:05 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/04 12:57:53 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_fd(int in_fd, int out_fd)
{
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != 0)
		dup2(out_fd, STDOUT_FILENO);
}

void	exec_child(t_cmd *cmd, char **env)
{
	int		ret;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		//manage fd (close and dup2)
		manage_fd(cmd->fd[0], cmd->fd[1]);
		execve(cmd->cmd_path, cmd->args, env);
	}
	waitpid(child, &ret, 0);
	set_return(ret);
}
