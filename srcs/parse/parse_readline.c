/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/19 17:31:23 by fcatinau         ###   ########.fr       */
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
		if (!add_tail_list(&list, check_token(*line, last), *line))
		{
			dellist(&list);
			return (false);
		}
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

static int	is_special_char(char c, char *is)
{
	while (*is)
	{
		if (c == *is)
			return (true);
		is++;
	}
	return (false);
}

// int	parse_readline(t_list *list, char *s)
// {
// 	char **line;

// 	line = ft_split(s, ' ');
// 	free(s);
// 	if (!line)
// 		return (false);
// 	move_in_list(line, list);
// 	tmp_print(list);
// 	return (true);
// }

int	word_in_list(t_list *list, int token, char *start, char *stop)
{
	char	*word;
	char	*tmp;

	if (start == stop)
		return (true);
	word = malloc(sizeof(char) * (stop - start) + 1);// malloc dont work need to see why ?
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

char	*special_elem_in_list(t_list *list, char *start, char *stop)
{
	char	quote;

	(void)list;
	(void)stop;
	quote = 0;
	if (*stop == '\'' || *stop == '\"' )
	{
		quote = *stop;
		stop++;
	}
	while (*stop != quote)
		stop++;
	stop++;
	word_in_list(list, WORD, start, stop);
	printf("first char = %c\n", start[0]);
	return (stop);
}

// echo  "test    "
// test
// ls /etc
int	parse_readline(t_list *list, char *s)
{
	char	*last;
	int		token;
	char	*free_word;

	token = WORD;
	free_word = s;
	last = s;
	while (*s)
	{
		if (is_special_char(*s, "'\"<|>$"))
		{
			s = special_elem_in_list(list, last, s);
			// special elem in list
		}
		else if (*s == ' ' && *s + 1 != '\0')
		{
			word_in_list(list, token, last, s);
			// go do a function for add a elem to a list
			token = WORD;
			last = s + 1;
		}
		s++;
	}
	if (*s)
		word_in_list(list, token, last, s);
	free(free_word);
	tmp_print(list);
	return (true);
}
