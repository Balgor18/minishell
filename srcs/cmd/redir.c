/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:47:52 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/05 16:48:28 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_file(t_node *iterator)
{
	if (iterator->token == APPEND)
	{
		return (open(iterator->word, O_WRONLY | O_CREAT | O_APPEND, 0644));
	}
	else
		return (open(iterator->word, O_WRONLY | O_TRUNC | O_CREAT, 0644));
}

void	switch_fd(int *fd, t_node *iterator, bool *file_error)
{
	if (iterator->prev->token == R_IN)
	{
		if (file_check(iterator->word) == true)
		{
			if (*fd != 0)
				close(*fd);
			*fd = open(iterator->word, O_RDONLY);
			if (*fd < 0)
			{
				printf("%s: %s\n", iterator->word, strerror(errno));
				*file_error = true;
				g_error = 1;
			}
		}
		else
		{
			g_error = 1;
			*file_error = true;
		}
	}
	else if (iterator->prev->token == APPEND)
	{
		if (*fd != 0)
			close(*fd);
		*fd = open(iterator->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd < 0)
		{
			printf("%s: %s\n", iterator->word, strerror(errno));
			*file_error = true;
			g_error = 1;
		}
	}
	else if (iterator->prev->token == R_OUT)
	{
		if (*fd != 0)
			close(*fd);
		*fd = open(iterator->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*fd < 0)
		{
			printf("%s: %s\n", iterator->word, strerror(errno));
			*file_error = true;
			g_error = 1;
		}
	}
}

int	check_redir(t_node *iterator, int fd[2], int next_pipe)
{
	int		i;
	bool	file_error;

	i = 0;
	file_error = false;
	if (iterator->token == PIPE)
	{
		if (iterator->next != NULL)
			iterator = iterator->next;
		else
			return (error_filename());
	}
	while (i < next_pipe)
	{
		if (iterator->token == R_IN || iterator->token == HEREDOC)
		{
			if (iterator->next != NULL)
			{
				iterator = iterator->next;
				i++;
			}
			else
			{
				return (error_filename());
			}
			switch_fd(&fd[0], iterator, &file_error);
			iterator = delnode(iterator, &iterator->list);
			iterator = delnode(iterator, &iterator->list);
		}
		else if (iterator->token == R_OUT || iterator->token == APPEND)
		{
			if (iterator->next != NULL)
			{
				iterator = iterator->next;
				i++;
			}
			else
			{
				return (error_filename());
			}
			switch_fd(&fd[1], iterator, &file_error);
			iterator = delnode(iterator, &iterator->list);
			iterator = delnode(iterator, &iterator->list);
		}
		if (file_error)
			break ;
		i++;
		iterator = iterator->next;
	}
	return (file_error);
}
