/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:21:41 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/15 11:47:31 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	which_cmd(t_node *iterator, int next_pipe)
{
	while (iterator->token != WORD)
		iterator = iterator->next;
	if (is_builtin(iterator->word) == true)
	{
		// manage builtin
	}
	else
	{
		// check path or just cmd
		if (ft_strchr(iterator->word, '/') == true)
		{
		// 		if path -> check relative / absolute 
			if (is_absolute_path(iterator->word) == true)
			{
				//exec command absolute path
			}
			else
			{
				// exec command relative path
			}
		}
		// exec cmd
	}

}

void	cmd_manage(t_node *iterator, int next_pipe)
{
	t_cmd	*cmd;
	int i;

	i = 0;
	init_cmd(cmd);
	ft_bzero(cmd->fd, sizeof(int) * 2);
	while (i < next_pipe) //1er jet sans les pipes
	{
		//check redir -> dup le fd de chaque redir
		check_redir(iterator, cmd->fd, next_pipe);
		//check cmd
		which_cmd(iterator, next_pipe);
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
