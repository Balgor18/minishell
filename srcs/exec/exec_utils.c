/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:18:07 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/29 23:23:51 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_node	*tmp;
	t_cmd	*bis;

	while (cmd)
	{
		while (cmd->arg)
		{
			tmp = cmd->arg;
			cmd->arg = tmp->next;
			free(tmp->word);
			free(tmp);
		}
		while (cmd->red)
		{
			cmd->red = tmp->next;
			tmp = cmd->red;
			free(tmp->word);
			free(tmp);
		}
		if (cmd->fd[IN] != 0)
			close(cmd->fd[IN]);
		if (cmd->fd[OUT] != 1)
			close(cmd->fd[OUT]);
		bis = cmd;
		cmd = bis->next;
		free(bis);
	}
}

int	create_heredoc(int type)
{
	int		ret;

	if (type)
	{
		ret = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (ret < 0)
			ret = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	else
	{
		ret = open("/tmp/.heredoc", O_RDONLY | O_CREAT, 0777);
		if (ret < 0)
			ret = open(".heredoc", O_RDONLY | O_CREAT, 0777);
	}
	return (ret);
}
