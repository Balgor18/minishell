/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:48:21 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/20 18:02:55 by fcatinau         ###   ########.fr       */
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
