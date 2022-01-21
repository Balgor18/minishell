/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/21 18:06:04 by fcatinau         ###   ########.fr       */
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
		dprintf(2, "------------\nArg\n------------\n");
		while (c->arg)
		{
			dprintf(2, "word = %s\ntoken = %d\n", c->arg->word, c->arg->token);
			c->arg = c->arg->next;
		}
		dprintf(2, "------------\nRed\n------------\n");
		while (c->red)
		{
			dprintf(2, "word = %s\ntoken = %d\n", c->red->word, c->red->token);
			c->red = c->red->next;
		}
		c = c->next;
	}
}

static void	exec_init_cmd(t_cmd **cmd, t_node *list)
{
	t_node	*tmp;
	t_cmd	*new;
	t_cmd	*start;

	start = *cmd;
	(*cmd)->arg = NULL;
	(*cmd)->red = NULL;
	(*cmd)->next = NULL;
	tmp = list;
	while (list)// check how i cant move th pointer and not free it
	{
		if (list->token == WORD)
		{
			if ((*cmd)->arg)
				ft_node_last((*cmd)->arg)->next = list;
			else
				(*cmd)->arg = list;
			tmp = list->next;
			list->next = NULL;
		}
		else if (list->token == PIPE)
		{
			new = malloc(sizeof(t_cmd));
			if (!new)
				return ;
			new->next = NULL;
			new->red = NULL;
			new->arg = NULL;
			ft_cmd_last((*cmd))->next = new;
			(*cmd) = (*cmd)->next;
			tmp = list->next;
		}
		else
		{
			if ((*cmd)->red)
				ft_node_last((*cmd)->red)->next = list;
			else
				(*cmd)->red = list;
			tmp = list->next;
			list->next = NULL;
		}
		list = tmp;
	}
	*cmd = start;
}

static void tmp_print_list(t_node *list)
{
	while (list)
	{
		dprintf(2, "word = %s\ntoken = %d\n", list->word, list->token);
		list = list->next;
	}
}
// export TEST="a b c d e"
//echo "Yolo" < $TEST

//echo "Yolo" < $TEST | $HOME 
//check cas $TEST = NULL
// $HOME NOT FOUND
void	exec(t_node *list)
{
	t_cmd	*cmd;

	tmp_print_list(list);
	exec_init_cmd(&cmd, list);
	tmp_print_cmd(cmd);
	free_list(list);
	delall_env();
	exit(126);
}
