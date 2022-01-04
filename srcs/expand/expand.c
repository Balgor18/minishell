/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/04 23:35:33 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	expand_double_quote(char **word, t_node *list)
// {
// 	(void)word;
// 	(void)list;
// }

// // do nothing just remove quote
// static void	expand_simple_quote(char **word, t_node *list)
// {
// 	(void)list;
// 	(void)word;
// }

// //have to create some new maillons in list
// static void	expand_no_quote(char **word, t_node *list)
// {
// 	(void)word;
// 	(void)list;
// }

// static void	expand_mode(char **tab)
// {
// 	while (*tab)
// 	{
// 		if (*tab == '\"')
// 		{
// 			expand_double_quote(tab, list);
// 			//do double quote fct
// 		}
// 		else if (*tab == '\'')
// 		{
// 			expand_simple_quote(tab, list);
// 			//do simple quote fct
// 		}
// 		else
// 		{
// 			expand_no_quote(tab, list);
// 		 	//do no_quote quote fct
// 		}
// 		tab++;
// 	}
// }

static int	start_word(char *word)
{
	int	start;

	start = 0;
	while (word[start] == ' ')
		start++;
	return (start);
}

static int	end_word(int start, char *word)
{
	int	quote;

	quote = NO_QUOTE;
	if (!word[start])
		return (0);
	if (word[start] != '\'' && word[start] != '"')
		return (start + 1);
	while (word[start])
	{
		if (word[start] == '\'' || word[start] == '"')
		{
			if (word[start] == '\'' && !quote)
				quote = SIMPLE;
			else if (word[start] == '"' && !quote)
				quote = DOUBLE;
			else if (quote != NO_QUOTE)
			{
				quote = NO_QUOTE;
				start++;
				break ;
			}
		}
		start++;
	}
	return (start);
}

static int	expand_split_rec(char ***tab, char *word, int index)
{
	int	i[MAX_SPLIT];

	i[START] = start_word(word);
	i[END] = end_word(i[START], word);
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
	char	**free_tab;

	free_tab = tab;
	while (*tab)
	{
		dprintf(2, "tab = %s\n", *tab);
		free(*tab);
		tab++;
	}
	free(free_tab);
}

static void	expand_split(t_node *list, t_node *next)
{
	char	**tab;

	tab = NULL;
	(void)next;
	expand_split_rec(&tab, list->word, 0);
	tmp_print(tab);
	// list->next = NULL;
	// list->next = next;// need to do this after adding with no quote
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
