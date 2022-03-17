/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:24:03 by fcatinau          #+#    #+#             */
/*   Updated: 2022/03/17 21:35:55 by fcatinau         ###   ########.fr       */
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

static int	expand_end_word(int beg, char *word)
{
	int	quote;

	quote = NO_QUOTE;
	if (!word[beg])
		return (0);
	if (word[beg] == '\'' || word[beg] == '"')
	{
		if (word[beg] == '\'')
			quote = SIMPLE;
		else if (word[beg] == '"')
			quote = DOUBLE;
	}
	while (word[++beg])
	{
		if (word[beg] == '\'' && quote == SIMPLE)
			return (beg + 1);
		if (word[beg] == '"' && quote == DOUBLE)
			return (beg + 1);
		if ((word[beg] == '\'' || word[beg] == '"') && !quote)
			break ;
		if (ft_strchr("<>|=", word[beg]) && !quote)
			return (++beg);
	}
	return (beg);
}

int	expand_quote_split_rec(char ***tab, char *word, int index)
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
	if (!expand_quote_split_rec(tab, list->word, 0))
		return (false);
	nb_word = ft_strlen_tab(*tab);
	(*tab) = expand_dollar_split((*tab), (*tab));
	(*rejoin) = ft_joinstr_from_tab((*tab), nb_word);
	if (!(*rejoin))
		return (false);
	return (true);
}

int	expand_quote_split(t_node *list, t_node **new, int token)
{
	char	**tab;
	char	*rejoin;

	if (!ft_strchr(list->word, '$'))
		return (expand_no_dollar_quote(list), false);
	tab = NULL;
	if (!expand_quote_split_bis(&rejoin, &tab, list))
		return (false);
	if (token == WORD)
		tab = ft_split(rejoin, ' ');
	else
		tab = only_one_line(rejoin);
	free(rejoin);
	if (!tab)
		return (free_tab(tab), false);
	if (!push_tab_in_list(new, tab))
	{
		free_tab(tab);
		return (false);
	}
	free_tab(tab);
	expand_token_in_new(list, new);
	return (true);
}
