/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:08:51 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/05 23:04:54 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '	')
		return (true);
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
	if (c == '\'')
	{
		if (!*quote)
			*quote = SIMPLE;
		else if (*quote == SIMPLE)
			*quote = NO_QUOTE;
		return (true);
	}
	else if (c == '"')
	{
		if (!*quote)
			*quote = DOUBLE;
		else if (*quote == DOUBLE)
			*quote = NO_QUOTE;
		return (true);
	}
	return (false);
}

int	split_end_word(char *line, int start)
{
	static int	quote = NO_QUOTE;

	if (line[start] == '\0')
		return (0);
	if (ft_strchr("<|>&", line[start]))
	{
		start++;
		while (ft_strchr("<>", line[start]))
			start++;
		return (start);
	}
	while (line[start])
	{
		is_start_or_end_quote(line[start], &quote);
		if ((line[start] == ' ' || ft_strchr("<|>&", line[start]))
			&& !quote)
			break ;
		start++;
	}
	return (start);
}
