/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:51:08 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/17 23:03:42 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

void	expand_space_neg(char *line)
{
	if (!line[0])
		return ;
	while (*line)
	{
		if (*line == ' ')
			*line = *line * -1;
		line++;
	}
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

void	expand_clear_list(t_node **list)
{
	printf("\n---------\nexpand_clear_list\n%p\n%p\n",*list, list);
	free((*list)->word);
	free(*list);
}
