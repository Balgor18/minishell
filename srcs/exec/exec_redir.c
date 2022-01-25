/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:44:00 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/25 10:47:57 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redir_rin(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->red->word, O_RDONLY);
	if (fd < 0)
		return (false);
	if (cmd->fd[IN] != 0)
		close(cmd->fd[IN]);
	cmd->fd[IN] = fd;
	return (true);
}

static int	exec_redir_rout(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->red->word, O_WRONLY);
	if (fd < 0)
		return (false);
	if (cmd->fd[OUT] != 1)
		close(cmd->fd[OUT]);
	cmd->fd[OUT] = fd;
	return (true);
}

static int	exec_redir_append(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->red->word, O_WRONLY | O_APPEND);
	if (fd < 0)
		return (false);
	if (cmd->fd[OUT] != 1)
		close(cmd->fd[OUT]);
	cmd->fd[OUT] = fd;
	return (true);
}

// if find a quote inside no expand to do.
// But if we got a dollar inside the limitor dont expand
void	exec_redir(t_cmd *cmd)
{
	t_cmd	*cpy;

	cpy = cmd;
	while (cpy->red)
	{
		if (cpy->red->token == R_IN)
			exec_redir_rin(cpy);
		else if (cpy->red->token == R_OUT)
			exec_redir_rout(cpy);
		else if (cpy->red->token == APPEND)
			exec_redir_append(cpy);
		else if (cpy->red->token == HEREDOC)
			exec_redir_heredoc(cpy);// <-- Need to to for expand on not expand
		cpy->red = cpy->red->next;
	}
}
