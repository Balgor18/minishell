/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:48:21 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/21 18:58:25 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_in_list(t_list *list, int token, char *start, char *stop)
{
	char	*word;
	char	*tmp;

	if (start == stop)
		return (true);
	word = malloc(sizeof(char) * (stop - start) + 1);
	if (!word)
		return (false);
	word[stop - start] = '\0';
	tmp = word;
	while (start < stop)
	{
		*word = *start;
		start++;
		word++;
	}
	if (!add_tail_list(&list, token, tmp))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	return (true);
}

char	*spc_quote_in_list(t_list *list, int *token, char *start, char *stop)
{
	char	quote;

	quote = 0;
	if (*stop == '\'' || *stop == '\"' )
	{
		quote = *stop;
		stop++;
	}
	while (*stop != quote)
		stop++;
	stop++;
	word_in_list(list, check_token(start, *token), start, stop);
	*token = check_token(start, WORD);
	return (stop);
}

char	*spc_rd_in_list(t_list *list, int *token, char *start, char *stop)
{
	char		rd;
	char		*mal;
	char		*tmp;
	char		*start2;

	rd = *stop;
	stop++;
	while (*stop == rd)
		stop++;
	mal = malloc(sizeof(char) * (stop - start) + 1);
	if (!mal)
		return (NULL);
	tmp = mal;
	mal[stop - start] = '\0';
	start2 = start;
	while (start != stop)
	{
		*mal = *start;
		start++;
		mal++;
	}
	word_in_list(list, check_token(tmp, *token), start2, stop);
	*token = check_token(tmp, WORD);
	free(tmp);
	return (stop);
}

char	*spc_prev_in_list(t_list *list, int *token, char *start, char *stop)
{
	char *word;
	char *free_word;

	word = malloc(sizeof(char) * (stop - start) + 1);
	if (!word)
		return (NULL);
	word[stop - start] = '\0';
	free_word = word;
	while (start != stop)
	{
		*word = *start;
		word++;
		start++;
	}
	add_tail_list(&list, check_token(free_word, WORD), free_word);
	*token = check_token(free_word, WORD);
	free(free_word);
	return (stop);
}

char	*parse_special(t_list *list, int *token, char *start)
{
	int		len;
	char	*word;
	char	*start2;
	char	*free_word;

	len = 0;
	start2 = start;
	while (is_special_char(*start, "<|>"))
	{
		start++;
		len++;
	}
	word = malloc(sizeof(char)* len + 1);
	if (!word)
		return (NULL);
	free_word = word;
	word[len] = '\0';
	start = start2;
	while (len > 0)
	{
		*word = *start;
		len--;
		word++;
		start++;
	}
	add_tail_list(&list, check_token(free_word, WORD), free_word);
	*token = check_token(free_word, WORD);
	free(free_word);
	return (start);
}

char	*spc_next_in_list(t_list *list, int *token, char *start, char *stop)
{
	// char *word;
	// char *free_word;

	start = parse_special(list, token, start);
	(void)stop;
	// while (!is_special_char(*start, " <|>") && *start)
	// {
	// 	*word = *start;
	// 	word++;
	// 	start++;
	// }
	// add_tail_list(&list, *token, free_word);
	// *token = check_token(free_word, WORD);
	// free(free_word);
	return (start);
}
