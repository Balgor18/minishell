/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/17 23:10:06 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo "$TEST'$TEST'$TEST"

//conditional jump
// echo "$TEST"'$TEST'$TEST
// echo "$TEST"'$TEST''$TEST'
// echo '$TEST'"$TEST"'$TEST'

// static void	tmp_print_list(t_node *l)
// {
// 	while (l)
// 	{
// 		dprintf(2, BLUE"w = %s\n"RED"t %d\n"RESET, l->word, l->token);
// 		l = l->next;
// 	}
// }

void	expand(t_node *list)
{
	t_node	*last;
	t_node	*start;

	start = list;
	last = start;
	dprintf(2, RED"Start expand\n"RESET);
	printf("entre de expand\n\n%p\n&%p", list, &list);
	while (start)
	{
		if (start->token == WORD || start->token == FD)
		{
			expand_quote_split(&start, start->next);
			if (start->next && last != start)
				last->next = start;
		}
		last = start;
		start = start->next;
	}
	printf("%s\n", list->word);
	free(list->word);
	free(list);
	delall_env();
	exit(126);
	return ;
}
