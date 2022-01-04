/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:55:05 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/03 13:51:14 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_args(t_node *iterator, t_cmd *cmd, t_list *line)
{
	t_node	*tmp;
	int		i;
	int		index;

	i = 0;
	index = 0;
	tmp = iterator;
	while(i < (int)iterator->list->lenght && tmp->token != PIPE)
	{
		tmp = tmp->next;
		i++;
	}
	cmd->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (cmd->args == NULL)
	{
		// Gestion d'erreur
	}
	ft_bzero(cmd->args, sizeof(char *) * (i + 1));
	while(index < i)
	{
		cmd->args[index] = ft_strdup(iterator->word); //pour la commande, peut etre mettre cmd->cmd_path
		index++;
		if (iterator->next)
			iterator = iterator->next;
	}
	tmp = NULL;
	while (i)
	{
		if (iterator->prev)
			tmp = iterator->prev;
		delnode(iterator, &line);
		if (tmp)
			iterator = tmp;
		i--;
	}
}