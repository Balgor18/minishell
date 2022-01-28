/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/28 01:35:06 by fcatinau         ###   ########.fr       */
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

// export TEST="a b c d e"
//echo "Yolo" < $TEST

//echo "Yolo" < $TEST | $HOME
//check cas $TEST = NULL
//$HOME NOT FOUND

void	exec(t_node *list)
{
	t_cmd	*cmd;

	cmd = NULL;
	exec_malloc_cmd(&cmd);
	exec_init_cmd(&cmd, list);
	exec_launch(cmd);
	delall_env();
	exit(126);
}
