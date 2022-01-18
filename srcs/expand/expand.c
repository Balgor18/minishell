/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/18 22:17:34 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo "$TEST'$TEST'$TEST"

//conditional jump
// echo "$TEST"'$TEST'$TEST
// echo "$TEST"'$TEST''$TEST'
// echo '$TEST'"$TEST"'$TEST'

static void	tmp_print_list(t_node *l)
{
	while (l)
	{
		dprintf(2, BLUE"w = %s\n"RED"t %d\n"RESET, l->word, l->token);
		l = l->next;
	}
}

static void	expand_modif_list(t_node **last, t_node **new,
	t_node **list, t_node **start)
{
	if (*last)
		(*last)->next = *new;
	if (*new)
		ft_node_last(*new)->next = (*start)->next;
	free((*start)->word);
	free(*start);
	*start = ft_node_last(*new);
	if (!*last)
	{
		*start = *new;
		*list = *start;
	}
}

void	expand(t_node *list)
{
	t_node	*last;
	t_node	*start;
	t_node	*new;

	new = NULL;
	start = list;
	last = NULL;
	dprintf(2, RED"Start expand\n"RESET);
	while (start)
	{
		if (start->token == WORD || start->token == FD)
		{
			if (expand_quote_split(start, &new))
				expand_modif_list(&last, &new, &list, &start);
			new = NULL;
		}
		last = start;
		if (start)
			start = start->next;
	}
	tmp_print_list(list);
	free_list(list);
	delall_env();
	exit(126);
	return ;
}
