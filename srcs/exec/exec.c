/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2022/03/17 21:34:05 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_last(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->next)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

void	exec(t_node *list)
{
	t_cmd	*cmd;

	cmd = NULL;
	exec_malloc_cmd(&cmd);
	if (!cmd)
		return ((void)delall(&list));
	exec_init_cmd(&cmd, list);
	if (!cmd)
		return ;
	exec_launch(cmd);
}
