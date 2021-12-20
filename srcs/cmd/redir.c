/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:47:52 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/20 16:34:36 by elaachac         ###   ########.fr       */
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

void	switch_fd(int fd, t_node *iterator)
{
	if (iterator->token == R_IN)
	{
		if (file_check(iterator->word) == true)
		{
			fd = open(iterator->word, O_RDONLY);
		}
		else
		{
			//gestion d'erreur redir in inexistante
		}
	}
	else if (iterator->token == APPEND)
	{
		fd = open(iterator->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		fd = open(iterator->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
}

int	check_redir(t_node *iterator, int *fd, int next_pipe)
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
	while (i < next_pipe && (iterator->token == R_IN || \
		iterator->token == HEREDOC || iterator->token == R_OUT || \
		iterator->token == APPEND)) // condition a changer
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
			switch_fd(*fd, iterator);
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
			switch_fd(*fd + 1, iterator);
		}
		delnode(iterator->next, &iterator->list);
		delnode(iterator, &iterator->list);
		i++;
		iterator = iterator->next;
	}
	return(0);
}
