/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/16 17:24:41 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo "$TEST'$TEST'$TEST"

//conditional jump
// echo "$TEST"'$TEST'$TEST
// echo "$TEST"'$TEST''$TEST'
// echo '$TEST'"$TEST"'$TEST'

void	expand(t_node *list)
{
	t_node	*last;
	t_node	*start;
	t_node	*next;

	start = list;
	last = start;
	while (start)
	{
		dprintf(2, "boucle \n");
		next = start->next;
		if (start->token == WORD || start->token == FD)
		{
			if (expand_quote_split(&start, next))
				last->next = start;
		}
		last = start;
		start = start->next;
	}
	return ;
}
