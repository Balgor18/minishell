/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/12 17:11:16 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// good WORD = Si ses pas autre choses ses un mot
//      FD = always after < > << >> |
// good LIMITOR = Cat du HEREDOC le mot apres et le limiteur || voir si autre cas
// good R_IN = Redirection in donc <
// good HEREDOC = Redirection << [LIMITEUR]
// good R_OUT = redirection out donc >
// good APPEND = >>
// good PIPE = |

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

int	move_in_list(char **line, t_list *list)
{
	char	**tmp;
	int		last;

	tmp = line;
	last = 0;
	while (*line)
	{
		add_tail_list(&list, check_token(*line, last), *line);
		last = check_token(*line, WORD);
		free(*line);
		line++;
	}
	free(tmp);
	return (true);
}

void	tmp_print(t_list *list)
{
	t_node	*node;

	node = list->head;
	while (node)
	{
		printf("world = %s\ntoken = %d\n-------\n", node->word, node->token);
		node = node->next;
	}
}

int	parse_readline(t_list *list, char *s)
{
	char **line;

	line = ft_split(s, ' ');
	free(s);
	if (!line)
		return (false);
	move_in_list(line, list);
	tmp_print(list);
	return (true);
}
