/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/12 13:02:49 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_start_word(char *word)
{
	int	start;

	start = 0;
	while (word[start] == ' ' && word[start])
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
		if (word[start] == '\'')
		{
			start++;
			if (quote == SIMPLE)
				break ;
		}
		else if (word[start] == '"')
		{
			start++;
			if (quote == DOUBLE)
				break ;
		}
		start++;
	}
	return (start);
}

static int	expand_quote_split_rec(char ***tab, char *word, int index)
{
	int	i[MAX_SPLIT];

	i[START] = expand_start_word(word);
	i[END] = expand_end_word(i[START], word);
	if (i[END] > 0)
	{
		if (!expand_quote_split_rec(tab, word + i[END], index + 1))
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

int	expand_remove_quote(char **line)
{
	char	*tmp;
	int		quote;

	if ((*line)[0] == '"')
	{
		quote = DOUBLE;
		tmp = ft_strtrim(*line, "\"");
	}
	else if ((*line)[0] == '\'')
	{
		quote = SIMPLE;
		tmp = ft_strtrim(*line, "'");
	}
	else
	{
		quote = NO_QUOTE;
		return (quote);
	}
	if (!tmp)
		return (SIMPLE);
	free(*line);
	*line = tmp;
	return (quote);
}

static int	expand_quote_split(t_node *list, t_node *next)
{
	char	**tab;
	char	*rejoin;

	if (!ft_strchr(list->word, '$'))
	{
		expand_remove_quote(&list->word);
		return (false);
	}

	tab = NULL;
	list->next = NULL;
	expand_quote_split_rec(&tab, list->word, 0);
	expand_dollar_split(tab);
	rejoin = ft_joinstr_from_tab(tab);
	if (!rejoin)
	{
		free_tab(tab);
		return (false);
	}
	tab = ft_split(rejoin, ' ');
	free(rejoin);
	if (!tab)
		return (false);
	delnode(&list);
	if (!push_tab_in_list(&list, tab))
		return (false);
	ft_node_last(list)->next = next;
	return (true);
}

//echo "$TEST'$TEST'$TEST"
//echo $$$$$$$$$$$$$$$$$$HOME$$$$$$$$$$$$$$
//echo "$HOME"'$home'
//echo "$TEST"'$TEST'$TEST

void	expand(t_node *list)
{
	t_node	*last;
	t_node	*start;
	t_node	*next;

	start = list;
	last = start;
	// dprintf(2, GREEN"Do expand \n"WHITE);
	while (start)
	{
		next = start->next;
		if (start->token == WORD || start->token == FD)
		{
			// dprintf(2, "last->word = %s\n", last->word);
			if (expand_quote_split(start, next))
				last->next = start;
			// dprintf(2, "start->word = %s\n", start->word);
		}
		last = start;
		start = start->next;
	}
	// dprintf(2, RED"End expand \n"WHITE);
	return ;
}
