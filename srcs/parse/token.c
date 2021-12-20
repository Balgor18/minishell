/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:48:41 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/20 17:48:51 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_or_append(char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (APPEND);
	if (s[0] == '<' && s[1] == '<')
		return (HEREDOC);
	return (WORD);
}

int	check_token(char *s, int last)
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
