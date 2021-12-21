/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:32 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/21 15:27:30 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	if ((*cmd)->env_path)
	{
		free((*cmd)->env_path);
		(*cmd)->env_path = NULL;
	}
	if ((*cmd)->cmd_path)
	{
		free((*cmd)->cmd_path);
		(*cmd)->cmd_path = NULL;
	}
	while ((*cmd)->args[i])
	{
		free((*cmd)->args[i]);
		(*cmd)->args[i] = NULL;
		i++;
	}
	if ((*cmd)->args)
		free((*cmd)->args);
	if ((*cmd))
		free((*cmd));
}

t_cmd	*init_cmd(t_list *list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->absolute_path = false;
	cmd->relative_path = false;
	cmd->no_path = false;
	cmd->built_in = false;
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->index = 0;
	cmd->env_path = ft_strdup(get_env_var(list->env , "PATH") + 5);
	ft_bzero(cmd->fd, sizeof(int) * 2);
	return (cmd);
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
