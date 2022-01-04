/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:58:56 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/04 13:20:54 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// good WORD = Si ses pas autre choses ses un mot
// good FD = always after < > << >>
// good LIMITOR = Cat du HDOC le mot apres et le limiteur || voir si autre cas
// good R_IN = Redirection in donc <
// good HDOC (HEREDOC)= Redirection << [LIMITEUR]
// good R_OUT = redirection out donc >
// good APPEND = >>
// good PIPE = |

static void	tmp_print(t_node *list)
{
	while (list)
	{
		printf(BLUE"world = |%s|\n"YELLOW"token = %d\n-------\n"RESET, list->word, list->token);
		list = list->next;
	}
}

static int	check_token2(char *s, int last)
{
	if (s[0] == '>' && s[1] == '>')
		return (APPEND);
	else if (s[0] == '<' && s[1] == '<')
		return (HEREDOC);
	else if (last == HEREDOC)
		return (LIMITOR);
	else if (last == APPEND || last == R_OUT || last == R_IN)
		return (FD);
	return (WORD);
}

static int	check_token(char *s, int last)
{
	size_t	len;

	len = ft_strlen(s);
	if (len == 1)
	{
		if (*s == '<')
			return (R_IN);
		else if (*s == '>')
			return (R_OUT);
		else if (*s == '|')
			return (PIPE);
	}
	return (check_token2(s, last));
}

void	tokeniser(t_node *list)
{
	t_node	*start;
	int		last;

	last = -1;
	start = list;
	while (start)
	{
		start->token = check_token(start->word, last);
		last = check_token(start->word, last);
		start = start->next;
	}
	tmp_print(list);
	if (!verif_parsing(list))
		delall(&list);
	if (list)
		expand(list);
	return ;
}
