/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:21:41 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/14 13:56:13 by elaachac         ###   ########.fr       */
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

int		find_pipe(t_node *iterator, int pos, int lenght)
{
	while(pos <= lenght)
	{
		if (iterator->token == PIPE)
			return (pos);
		pos++;
		iterator = iterator->next;
	}
	return(pos);
}

void	check_redir(t_node *iterator, int *fd, int next_pipe)
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
	while (i < next_pipe) // condition a changer
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
			switch_fd(fd, iterator); // fct pour ouvrir et dup les fd
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
			switch_fd(fd + 1, iterator);
		}
		delnode(iterator->next, iterator->list);
		delnode(iterator, iterator->list);
		i++;
		iterator = iterator->next;
	}
	//Delete node => le node de l'operateur et le node du fichier
	// Donc iterator et iterator->prev
}

void	cmd_manage(t_node *iterator, int next_pipe)
{
	int	fd[2];
	int i;

	i = 0;
	ft_bzero(fd, sizeof(int) * 2);
	while (i < next_pipe) //1er jet sans les pipes
	{
		//check redir -> dup le fd de chaque redir
		check_redir(iterator, fd, next_pipe);
		//check cmd
		which_cmd();
		//exec cmd
		exec_cmd();
	}
}

void	exec(t_list *line)
{
	t_node	*iterator;
	int		lenght;
	int		next_pipe;

	next_pipe = 0;
	iterator = line->head;
	lenght = line->lenght;
	file_opener();
	while (lenght)
	{
		next_pipe = find_pipe(iterator,line->lenght - lenght, line->lenght);
		cmd_manage(iterator, next_pipe);
		lenght -= next_pipe;
	}
}
