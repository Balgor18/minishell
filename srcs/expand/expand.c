/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/14 19:18:36 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tmp_print_list(t_node *list)
{
	while (list)
	{
		printf(PURPLE"mot = %s\n"YELLOW"token = %d\n"RESET, list->word, list->token);
		list = list->next;
	}
}

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

	// delall_env();
	// delall(&g_debug);
	// printf("%s\n", *line);
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
	// printf("%s = %p\n", tmp, tmp);
	if (!tmp)
		return (SIMPLE);
	// printf("line free\n");
	free(*line);
	*line = tmp;
	// printf("line = %s\n", *line);
	// exit(128);
	return (quote);
}

static int	expand_quote_split(t_node **list, t_node *next)
{
	char	**tab;
	char	*rejoin;

	if (!ft_strchr((*list)->word, '$'))
	{
		expand_remove_quote(&(*list)->word);
		return (false);
	}
	tab = NULL;
	(*list)->next = NULL;
	expand_quote_split_rec(&tab, (*list)->word, 0);
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
	free((*list)->word);
	free(*list);
	if (!push_tab_in_list(list, tab))
	{
		free_tab(tab);
		return (false);
	}
	free_tab(tab);
	if (next)
		ft_node_last(*list)->next = next;// problem here
	else
		ft_node_last(*list)->next = NULL;
	// printf("list->next = %p\nnext = %p\n", (*list)->next, next);
	return (true);
}

//echo "$TEST'$TEST'$TEST"

// invalid free
//echo $$$$$$$$$$$$$$$$$$HOME$$$$$$$$$$$$$$

// Conditional jump or move 
//echo "$HOME"'$home'

//leaks error
// echo "$TEST"'$TEST'$TEST
// echo "$TEST"'$TEST''$TEST'

// leaks error
// echo '$TEST'"$TEST"'$TEST'
void	expand(t_node *list)
{
	t_node	*last;
	t_node	*start;
	t_node	*next;

	start = list;
	last = start;
	// dprintf(2, GREEN"Do expand \n"WHITE);
	// printf(BLUE"Print list\n"RESET);
	// tmp_print_list(list);
	while (start)
	{
		next = start->next;
		if (start->token == WORD || start->token == FD)
		{
			// dprintf(2, "last->word = %s\n", last->word);
			if (expand_quote_split(&start, next))
			{
				last->next = start;
				// printf("------------\nlast\n%p\n%s\n%d\n%p\n------------\n", last, last->word, last->token, last->next);
				// printf("------------\nstart\n%p\n%s\n%d\n%p\n------------\n", start, start->word, start->token, start->next);
				// if (next)
				// 	printf("------------\nnext\n%p\n%s\n%d\n%p\n------------\n", next, next->word, next->token, next->next);
				// printf("----------------\n");
				// tmp_print_list(list);
				// printf("----------------\n");
				start = start->next;
			}
			// dprintf(2, "start->word = %s\n", start->word);
		}
		last = start;
		start = start->next;
	}
	// tmp_print_list(list);
	delall(&list);
	// dprintf(2, RED"End expand \n"WHITE);
	delall_env();
	exit(126);
	return ;
}
