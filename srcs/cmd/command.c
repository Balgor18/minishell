/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:21:41 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/11 22:25:48 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_node *iterator)
{
	if (iterator->token == R_IN || iterator->token == R_OUT ||\
		 iterator->token == HEREDOC ||  iterator->token == APPEND)
		return(true);
	else
		return (false);
}

int	count_redir(t_node *iterator, int lenght)
{
	int	nbr_redir;

	nbr_redir = 0;
	while(lenght)
	{
		nbr_redir += is_redir(iterator);
		iterator = iterator->next;
		lenght--;
	}
	return(nbr_redir);
}

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

void	cmd_manage(t_node *iterator)
{
	(void)iterator;
	//todo
}

void	exec(t_list *line)
{
	t_node	*iterator;
	int		lenght = 0;
	int		next_pipe = 0;

	iterator = line->head;
	// lenght = line->lenght;
	while (lenght)
	{
		// next_pipe = find_pipe(iterator,line->lenght - lenght, line->lenght);
		// cmd_manage();
		lenght -= next_pipe;
	}
}
