/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/29 16:26:44 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand(t_list *list, char **env)
{
	t_node	*node;

	node = list->head;
	(void)env;
	dprintf(2, "Do expand \n");
	while (node)
	{
		node = node->next;
	}
	dprintf(2, "End expand \n");
	return (false);
	return (true);
}
