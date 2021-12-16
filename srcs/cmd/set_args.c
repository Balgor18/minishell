/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:55:05 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/16 18:25:03 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_args(t_node *iterator, t_cmd *cmd, int next_pipe)
{
	t_node	*tmp;
	int		i;
	int		index;

	i = 0;
	index = 0;
	tmp = iterator;
	while(tmp->token != PIPE && i < tmp->list->lenght)
	{
		tmp = tmp->next;
		i++;
	}
	cmd->args = (char **)malloc(sizeof(char *) * i);
	if (cmd->args == NULL)
	{
		// Gestion d'erreur
	}
	while(index <= i)
	{
		cmd->args[index] = ft_strdup(iterator->word); //pour la commande, peut etre mettre cmd->cmd_path
		i++;
		iterator = iterator->next;
	}
	while (i)
	{
		delnode(iterator, iterator->list);
		i--;
	}
}
