/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:18:07 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/26 18:37:20 by fcatinau         ###   ########.fr       */
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
			tmp = ((cmd->arg = tmp->next, cmd->arg));
			free(tmp->word);
			free(tmp);
		}
		while (cmd->red)
		{
			tmp = ((cmd->red = tmp->next, cmd->red));
			free(tmp->word);
			free(tmp);
		}
		if (cmd->fd[IN] != 0)
			close(cmd->fd[IN]);
		if (cmd->fd[OUT] != 1)
			close(cmd->fd[OUT]);
		bis = ((cmd = bis->next, cmd));
		free(bis);
	}
}

int	create_heredoc(int type)
{
	int		ret;

	if (type)
	{
		ret = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC);
		if (ret < 0)
			ret = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC);
	}
	else
	{
		ret = open("/tmp/.heredoc", O_RDONLY | O_CREAT);
		if (ret < 0)
			ret = open(".heredoc", O_RDONLY | O_CREAT);
	}
	return (ret);
}
