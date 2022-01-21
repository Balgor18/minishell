/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/21 18:21:25 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	absolut_char(char **word)
{
	char	*tmp;

	tmp = *word;
	while (*tmp)
	{
		if (*tmp == -32)
			*tmp *= -1;
		tmp++;
	}
}

static void	expand_absolut_char(t_node *list)
{
	while (list)
	{
		absolut_char(&list->word);
		list = list->next;
	}
}

static void	expand_modif_list(t_node **last, t_node **new,
	t_node **list, t_node **start)
{
	t_node	*tmp;

	tmp = (*start)->next;
	if (*last)
		(*last)->next = *new;
	if (*new)
		ft_node_last(*new)->next = tmp;
	free((*start)->word);
	free(*start);
	*start = tmp;
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
	expand_absolut_char(list);
	if (list)
		exec(list);
	return ;
}
