/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:44:00 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/07 18:05:44 by fcatinau         ###   ########.fr       */
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
		return (exec_redir_heredoc(cpy));
	return (true);
}

int	exec_redir(t_cmd *cmd)
{
	t_cmd	*cpy;
	t_node	*red;
	int		ret;

	red = ((cpy = cmd, ret = true, cmd->red));
	while (cpy->red)
	{
		if (cpy->red->token == R_IN)
		{
			if (!exec_redir_rin(cpy))
				return (g_error = 1, false);
		}
		else if (cpy->red->token == R_OUT)
			if (!exec_redir_rout(cpy))
				return (g_error = 1, false);
		ret = exec_redir_2(cpy);
		if (ret != true)
			break ;
		cpy->red = cpy->red->next;
	}
	if (cpy->red)
		return (g_error = 1, ret);
	cmd->red = red;
	return (true);
}
