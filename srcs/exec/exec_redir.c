/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:44:00 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/03 18:45:04 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redir_rin(t_cmd *cmd)
{
	int		fd;
	char	*name;

	name = cmd->red->next->word;
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror(name);
		return (false);
	}
	if (cmd->fd[IN] != 0)
	{
		dup2(fd, cmd->fd[IN]);
		close(cmd->fd[IN]);
	}
	cmd->fd[IN] = fd;
	return (true);
}

static int	exec_redir_rout(t_cmd *cmd)
{
	int		fd;
	char	*name;

	name = cmd->red->next->word;
	fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		perror(name);
		return (false);
	}
	if (cmd->fd[OUT] != 1)
	{
		dup2(fd, cmd->fd[OUT]);
		close(cmd->fd[OUT]);
	}
	cmd->fd[OUT] = fd;
	return (true);
}

static int	exec_redir_append(t_cmd *cmd)
{
	int		fd;
	char	*name;

	name = cmd->red->next->word;
	fd = open(name, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(name);
		return (false);
	}
	if (cmd->fd[OUT] != 1)
	{
		dup2(fd, cmd->fd[OUT]);
		close(cmd->fd[OUT]);
	}
	cmd->fd[OUT] = fd;
	return (true);
}

static int	exec_redir_2(t_cmd *cpy)
{
	if (cpy->red->token == APPEND)
	{
		if (!exec_redir_append(cpy))
			return (false);
	}
	else if (cpy->red->token == HEREDOC)
	{
		if (!exec_redir_heredoc(cpy))
			return (false);
	}
	return (true);
}

int	exec_redir(t_cmd *cmd)
{
	t_cmd	*cpy;
	t_node	*red;

	red = ((cpy = cmd, cmd->red));
	while (cpy->red)
	{
		if (cpy->red->token == R_IN)
		{
			if (!exec_redir_rin(cpy))
				break ;
		}
		else if (cpy->red->token == R_OUT)
		{
			if (!exec_redir_rout(cpy))
				break ;
		}
		if (!exec_redir_2(cpy))
			break ;
		cpy->red = cpy->red->next;
	}
	if (cpy->red)
		return (false);
	cmd->red = red;
	return (true);
}
