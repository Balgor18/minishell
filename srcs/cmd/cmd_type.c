/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:32 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/15 13:50:26 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd **cmd)
{
	(*cmd)->absolute_path = false;
	(*cmd)->relative_path = false;
	(*cmd)->args = NULL;
	(*cmd)->cmd = NULL;
	ft_bzero((*cmd)->fd, sizeof(int) * 2);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == true || ft_strcmp(cmd, "cd") == true || \
		ft_strcmp(cmd, "pwd") == true || ft_strcmp(cmd, "export") == true || \
		ft_strcmp(cmd, "unset") == true || ft_strcmp(cmd, "env") == true || \
		ft_strcmp(cmd, "exit") == true)
		return (true);
	else
		return (false);
}

bool	is_absolute_path(char *cmd)
{
	if (cmd[0] == '/')
		return (true);
	else
		return (false);
}
