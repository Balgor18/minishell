/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:21:41 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/04 16:53:32 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_pipe(t_node *iterator, int pos, int lenght)
{
	while(pos < lenght)
	{
		if (iterator->token == PIPE)
			return (pos);
		pos++;
		iterator = iterator->next;
	}
	return(pos);
}

void	which_cmd(t_node *iterator, t_cmd **cmd)
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
				(*cmd)->absolute_path = true;
				(*cmd)->cmd_path = ft_strdup(iterator->word);
			}
			else
			{
				(*cmd)->relative_path = true;
				(*cmd)->cmd_path = ft_strjoin(get_pwd(), iterator->word);
			}
		}
		else
		{
			(*cmd)->no_path = true;
			find_path(iterator->word, *cmd);
		}
	}
}

void	exec_cmd(t_list	*list, t_cmd **cmd)
{
	if ((*cmd)->built_in == true)
	{
		//manage built in exec
	}
	else
	{
		exec_child(*cmd, list->env);
	}
}

void	cmd_manage(t_node *iterator, t_list *line, int next_pipe)
{
	t_cmd	*cmd;
	int i;

	// cmd = NULL;
	i = 0;
	cmd = init_cmd(iterator->list);
	while (i < next_pipe) //1er jet sans les pipes
	{
		//check redir -> dup le fd de chaque redir
		if (check_redir(iterator, cmd->fd, next_pipe) == 1)
		//check cmd
		which_cmd(iterator, &cmd);
		//exec cmd
		set_args(iterator, cmd, line);
		exec_cmd(line, &cmd);
		free_cmd(&cmd);
		i += next_pipe;
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
	// file_opener(); -> ouvrir les fd
	while (lenght)
	{
		next_pipe = find_pipe(iterator,line->lenght - lenght, line->lenght);
		cmd_manage(iterator, line, next_pipe);
		lenght -= next_pipe;
	}
}
