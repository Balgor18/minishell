/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:24:03 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/18 19:05:33 by fcatinau         ###   ########.fr       */
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
	while (word[++start])
	{
		if (word[start] == '\'')
		{
			if (quote == SIMPLE)
				return (++start);
		}
		else if (word[start] == '"')
			if (quote == DOUBLE)
				return (++start);
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

static int	expand_quote_split_bis(char **rejoin, char ***tab, t_node *list)
{
	int	nb_word;

	*rejoin = NULL;
	expand_quote_split_rec(tab, list->word, 0);
	nb_word = ft_strlen_tab(*tab);
	(*tab) = expand_dollar_split((*tab), (*tab));
	(*rejoin) = ft_joinstr_from_tab((*tab), nb_word);
	if (!(*rejoin))
	{
		free_tab((*tab));
		return (false);
	}
	return (true);
}

int	expand_quote_split(t_node *list, t_node **new)
{
	char	**tab;
	char	*rejoin;

	if (!ft_strchr(list->word, '$'))
	{
		expand_remove_quote(&(list)->word);
		return (false);
	}
	tab = NULL;
	expand_quote_split_bis(&rejoin, &tab, list);
	tab = ft_split(rejoin, ' ');
	free(rejoin);
	if (!tab)
		return (false);
	if (!push_tab_in_list(new, tab))
	{
		free_tab(tab);
		return (false);
	}
	free_tab(tab);
	return (true);
}
