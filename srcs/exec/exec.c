/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/24 17:54:11 by fcatinau         ###   ########.fr       */
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

static void	tmp_print_cmd(t_cmd *c)
{
	while (c)
	{
		if (c->arg)
			dprintf(2, "------------\nArg\n------------\n");
		else
			dprintf(2, BLUE"Arg empty\n"RESET);
		while (c->arg)
		{
			dprintf(2, "word = %s\ntoken = %d\n", c->arg->word, c->arg->token);
			c->arg = c->arg->next;
		}
		if (c->red)
			dprintf(2, "------------\nRed\n------------\n");
		else
			dprintf(2, BLUE"Red empty\n"RESET);
		while (c->red)
		{
			dprintf(2, "word = %s\ntoken = %d\n", c->red->word, c->red->token);
			c->red = c->red->next;
		}
		dprintf(2, RED"-------------------------------------------\n"RESET);
		c = c->next;
	}
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
	tmp_print_cmd(cmd);
	delall_env();
	exit(126);
}
