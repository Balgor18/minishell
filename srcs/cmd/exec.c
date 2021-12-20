/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:26:05 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/20 18:45:01 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_cmd *cmd, char **env)
{
	int		ret;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		//manage fd (close and dup2)
		execve(cmd->cmd_path, cmd->args, env);
	}
	waitpid(child, &ret, 0);
}