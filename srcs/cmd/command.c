/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:21:41 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/15 18:10:59 by elaachac         ###   ########.fr       */
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

void	which_cmd(t_node *iterator, t_cmd **cmd, int next_pipe)
{
	while (iterator->token != WORD)
		iterator = iterator->next;
	if (is_builtin(iterator->word) == true)
	{
		// manage builtin
		(*cmd)->built_in = true;
	}
	else
	{
		// check path or just cmd
		if (ft_strchr(iterator->word, '/') == true)
		{
		// 		if path -> check relative / absolute
			if (is_absolute_path(iterator->word) == true)
			{
				(*cmd)->relative_path = true;
				(*cmd)->cmd_path = ft_strdup(iterator->word);
			}
			else
			{
				(*cmd)->absolute_path = true;
				(*cmd)->cmd_path = ft_strdup(iterator->word);
			}
		}
		else
		{
			(*cmd)->no_path = true;
			find_path(iterator->word, cmd);
		}
	}
}

// void	exec_cmd(t_node	*iterator, t_cmd **cmd, int next_pipe)
// {
// 	if ()
// }

void	cmd_manage(t_node *iterator, int next_pipe, char **env)
{
	t_cmd	*cmd;
	int i;

	i = 0;
	init_cmd(cmd);
	while (i < next_pipe) //1er jet sans les pipes
	{
		//check redir -> dup le fd de chaque redir
		check_redir(iterator, cmd->fd, next_pipe);
		//check cmd
		which_cmd(iterator, cmd, next_pipe);
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
