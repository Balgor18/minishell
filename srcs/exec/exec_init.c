/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:06:31 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/24 13:11:12 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_malloc_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return ;
	tmp->arg = NULL;
	tmp->red = NULL;
	tmp->next = NULL;
	if (*cmd)
		ft_cmd_last(*cmd)->next = tmp;
	else
		*cmd = tmp;
	return ;
}

static t_node	*exec_add_arg(t_cmd **cmd, t_node *list)
{
	t_node	*tmp;

	if ((*cmd)->arg)
		ft_node_last((*cmd)->arg)->next = list;
	else
		(*cmd)->arg = list;
	tmp = list->next;
	list->next = NULL;
	return (tmp);
}

static t_node	*exec_add_red(t_cmd **cmd, t_node *list)
{
	t_node	*tmp;

	if ((*cmd)->red)
		ft_node_last((*cmd)->red)->next = list;
	else
		(*cmd)->red = list;
	tmp = list->next;
	list->next = NULL;
	return (tmp);
}

void	exec_init_cmd(t_cmd **cmd, t_node *list)
{
	t_node	*tmp;
	t_cmd	*start;

	start = *cmd;
	tmp = list;
	while (list)
	{
		if (list->token == WORD)
			tmp = exec_add_arg(cmd, list);
		else if (list->token == PIPE)
		{
			tmp = list->next;
			free(list->word);
			free(list);
			exec_malloc_cmd(cmd);
			(*cmd) = (*cmd)->next;
		}
		else
			tmp = exec_add_red(cmd, list);
		list = tmp;
	}
	*cmd = start;
}
