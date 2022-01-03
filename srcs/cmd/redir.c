/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:47:52 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/03 17:31:44 by elaachac         ###   ########.fr       */
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

void	switch_fd(int *fd, t_node *iterator)
{
	if (iterator->token == R_IN)
	{
		if (file_check(iterator->word) == true)
		{
			*fd = open(iterator->word, O_RDONLY);
		}
		else
		{
			g_error = 1;
		}
	}
	else if (iterator->token == APPEND)
	{
		*fd = open(iterator->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		*fd = open(iterator->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
}

int	check_redir(t_node *iterator, int fd[2], int next_pipe)
{
	int i;

	i = 0;
	if (iterator->token == PIPE)
	{
		if (iterator->next != NULL)
			iterator = iterator->next;
		else
			return (error_filename());
	}
	while (i < next_pipe) // condition changee, ps surquece soit la bonne
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
			switch_fd(&fd[0], iterator);
			delnode(iterator->next, &iterator->list);
			delnode(iterator, &iterator->list);
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
			switch_fd(&fd[1], iterator);
			iterator = delnode(iterator, &iterator->list);
			iterator = delnode(iterator, &iterator->list);
		}
		i++;
		iterator = iterator->next;
	}
	return(0);
}
