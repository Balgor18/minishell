/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/10 02:17:05 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(char *s)
{
	(void)s;
	//do nothing
	return (WORD);
}

int	move_in_list(char **line, t_list *list)
{
	char **tmp;

	tmp = line;
	while (*line)
	{
		add_tail_list(&list, check_token(*line), *line);
		free(*line);
		line++;
	}
	free(tmp);
	return (true);
}

int	parse_readline(t_list *list, char *s)
{
	char **line;

	line = ft_split(s, ' ');
	if (!line)
		return (false);
	free(s);
	move_in_list(line, list);
	return (true);
}
