/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/10 22:37:09 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_start_word(char *word)
{
	int	start;

	start = 0;
	while (word[start] == ' ')
		start++;
	return (start);
}

static int	expand_end_word(int start, char *word)
{
	int	quote;

	quote = NO_QUOTE;
	if (!word[start])
		return (0);
	if (word[start] == '\'' || word[start] == '"')
	{
		if (word[start] == '\'')
			quote = SIMPLE;
		else if (word[start] == '"')
			quote = DOUBLE;
		start++;
	}
	while (word[start])
	{
		if (word[start] == '\'' || word[start] == '"')
		{
			if (quote != NO_QUOTE)
				start++;
			break ;
		}
		start++;
	}
	return (start);
}

// Split on every '" or ' '

static int	expand_split_rec(char ***tab, char *word, int index)
{
	int	i[MAX_SPLIT];

	i[START] = expand_start_word(word);
	i[END] = expand_end_word(i[START], word);
	if (i[END] > 0)
	{
		if (!expand_split_rec(tab, word + i[END], index + 1))
			return (false);
		(*tab)[index] = ft_substr(word, i[START], i[END] - i[START]);
		if (!(*tab)[index])
			return (false);
	}
	else if (i[END] == 0)
	{
		(*tab) = (char **)malloc(sizeof(char *) * (index + 1));
		if (!(*tab))
			return (false);
		(*tab)[index] = NULL;
	}
	return (true);
}

static void	tmp_print(char **tab)
{
	while (*tab)
	{
		dprintf(2, BLUE"|%s|\n"YELLOW"--------\n"RESET, *tab);
		tab++;
	}
}

static void	expand_split(t_node *list, t_node *next)
{
	t_node	*tmp;
	char	**tab;

	tmp = list->next;
	list->next = NULL;
	tab = NULL;
	(void)next;
	expand_split_rec(&tab, list->word, 0);
	expand_find_dollar(tab);//->did i need to send elem
	tmp_print(tab);
	list->next = tmp;// need to do this after adding with no quote
}

void	expand(t_node *list)
{
	t_node	*start;

	start = list;
	dprintf(2, GREEN"Do expand \n"WHITE);
	while (start)
	{
		if (start->token == WORD || start->token == FD)
			expand_split(start, start->next);
		start = start->next;
	}
	dprintf(2, RED"End expand \n"WHITE);
	return ;
}
