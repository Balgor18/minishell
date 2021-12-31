/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:12:55 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/31 18:22:21 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_parsing(t_list *list)
{
	t_node	*node;
	int		last_token;

	last_token = -1;
	node = list->head;
	while (node)
	{
		if (node->token != WORD && last_token != WORD && last_token != -1)
		{
			g_error = 2;// syntax error --> print line of syntax ??
			break ;
		}
		if (last_token == -1)
			last_token = node->token;
		node = node->next;
	}
	return (true);
}
