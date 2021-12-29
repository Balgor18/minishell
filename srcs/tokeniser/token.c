/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:58:56 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/23 23:43:37 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_or_append(char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (APPEND);
	if (s[0] == '<' && s[1] == '<')
		return (HEREDOC);
	return (WORD);
}

static int	check_token(char *s, int last)
{
	size_t	len;

	len = ft_strlen(s);
	if (last == HEREDOC)
		return (LIMITOR);
	if (last == APPEND || last == PIPE || last == R_OUT || last == R_IN)
		return (FD);
	if (len == 1)
	{
		if (*s == '<')
			return (R_IN);
		else if (*s == '>')
			return (R_OUT);
		else if (*s == '|')
			return (PIPE);
	}
	else if (len == 2)
		return (heredoc_or_append(s));
	return (WORD);
}

int	tokeniser(t_list *list)
{
	int		last;
	t_node	*tmp;

	last = WORD;
	tmp = list->head;
	while (tmp)
	{
		tmp->token = check_token(tmp->word, last);
		last = check_token(tmp->word, last);
		tmp = tmp->next;
	}
	return (true);
}
