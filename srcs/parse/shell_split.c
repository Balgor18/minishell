/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:08:51 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/22 18:26:15 by fcatinau         ###   ########.fr       */
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

int	split_end_word(char *line, int start)
{
	static int	quote = NO_QUOTE;

	while (line[start])
	{
		if (line[start] == '\'')
		{
			if (quote == NO_QUOTE)
				quote = SIMPLE;
			else if (quote == SIMPLE)
			{
				quote = NO_QUOTE;
				start++;
				break ;
			}
		}
		else if (line[start] == '"')
		{
			if (quote == NO_QUOTE)
				quote = DOUBLE;
			else if (quote == DOUBLE)
			{
				quote = NO_QUOTE;
				start++;
				break ;
			}
		}
		else if (line[start] == ' ' && !quote)
			break;
		else if (is_specify_char(line[start], "<|>&") && !quote)
		{
			start++;
			break ;
		}
		start++;
	}
	return (start);
}

int	shell_split_rec(char ***tab, char *line, int index)
{
	int	i[MAX_SPLIT];

	i[START] = split_start_word(line);
	i[END] = split_end_word(line, i[START]);
	if (i[END] > 0)
	{
		if (!shell_split_rec(tab, line + i[START] + i[END], index + 1))
			return (false);
		(*tab)[index] = ft_substr(line, i[START], i[END] - i[START]);
		if (!(*tab)[index])
			return (false);
	}
	else if (i[END] == 0)
	{
		(*tab) = (char **)malloc(sizeof(char *) * index + 1);
		if (!(*tab))
			return (false);
		(*tab)[index] = NULL;
	}
	return (true);
}

static void	tmp_print(char **tab)
{
	int	index;

	index = -1;
	while (tab[++index])
	{
		printf("%s\n", tab[index]);
	}
}

int	shell_split(char ***tab, char *line)
{
	if (!shell_split_rec(tab, line, 0))
		return (false);
	tmp_print(*tab);
	return (true);
}
