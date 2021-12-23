/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:08:51 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/23 22:36:18 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '	')
		return (true);
	return (false);
}

static int	is_specify_char(char c, char *s)
{
	while (*s)
	{
		if (c == *s)
			return (true);
		s++;
	}
	return (false);
}

int	split_start_word(char *line)
{
	int	ret;

	ret = 0;
	while (is_whitespace(*line))
	{
		ret++;
		line++;
	}
	return (ret);
}

static int	is_start_or_end_quote(char c, int *quote)
{
	if (c == '\'' && !*quote)
	{
		if (!*quote)
			*quote = SIMPLE;
		else
			*quote = NO_QUOTE;
		return (true);
	}
	else if (c == '"')
	{
		if (!*quote)
			*quote = DOUBLE;
		else
			*quote = NO_QUOTE;
		return (true);
	}
	return (false);
}

int	split_end_word(char *line, int start)
{
	static int	quote = NO_QUOTE;

	if (is_specify_char(line[start], "<|>&"))
	{
		while (is_specify_char(line[start], "<|>&"))
			start++;
		return (start);
	}
	while (line[start])
	{
		if (is_start_or_end_quote(line[start], &quote))
		{
			if (!quote)
			{
				start++;
				break ;
			}
		}
		else if (line[start] == ' ' && !quote)
			break ;
		else if (is_specify_char(line[start], "<|>&") && !quote)
			break ;
		start++;
	}
	return (start);
}
