/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/11 18:36:39 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// good WORD = Si ses pas autre choses ses un mot
//      FD = Dont know need Check || Probably useless
// good LIMITOR = Cat du HEREDOC le mot apres et le limiteur || voir si autre cas
// good R_IN = Redirection in donc <
// good HEREDOC = Redirection << [LIMITEUR]
// good R_OUT = redirection out donc >
// good APPEND = >>
// good PIPE = |

int	heredoc_or_append(char *s)
{
	if (*s == '>' && *s + 1 == '>')
		return (APPEND);
	return (HEREDOC);
}

int	check_token(char *s, int last)
{
	size_t	len;

	len = ft_strlen(s);
	if (last == HEREDOC)
		return (LIMITOR);
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

// t_list	*move_in_list(char **line, t_list *list)
// {
// 	char	**tmp;
// 	int		last;

// 	tmp = line;
// 	last = 0;
// 	while (*line)
// 	{
// 		if (!add_tail_list(&list, check_token(*line, last), *line))
// 			return (NULL);
// 		last = check_token(*line , 0);
// 		printf("%p\n%p\n", list->list->word, &list->list->token);
// 		printf("2 world = %s\ntoken = %d\n-------\n", list->list->word, list->list->token);
// 		free(*line);
// 		printf("%p\n%p\n", list->list->word, &list->list->token);
// 		printf("3 world = %s\ntoken = %d\n-------\n", list->list->word, list->list->token);
// 		line++;
// 		printf("%p\n%p\n", list->list->word, &list->list->token);
// 		printf("4 world = %s\ntoken = %d\n-------\n", list->list->word, list->list->token);
// 	}
// 	free(tmp);
// 	printf("5 world = %s\ntoken = %d\n-------\n", list->list->word, list->list->token);
// 	return (list);
// }

void	tmp_print(t_list *list)
{
	t_node	*node;

	node = list->head;
	while (node)
	{
		printf("8 world = %s\ntoken = %d\n-------\n", node->word, node->token);
		node = node->next;
	}
}

// int	parse_readline(t_list *list, char *s)
// {
// 	char **line;

// 	line = ft_split(s, ' ');
// 	free(s);
// 	if (!line)
// 		return (false);
// 	list = move_in_list(line, list);
// 	printf("Jai quoi dans list ?\n%p\n", list->list);
// 	printf("7 world = %s\ntoken = %d\n-------\n", list->list->word, list->list->token);
// 	if (!list)
// 		return (false);
// 	tmp_print(list);
// 	return (true);
// }

t_list	*move_in_list(char **line, t_list *list)
{
	char	**tmp;
	int		last;
	int		i;

	i = -1;
	tmp = line;
	last = 0;
	while (line[++i])
	{
		if (!add_tail_list(&list, check_token(line[i], last), line[i]))
			return (NULL);
		last = check_token(line[i] , 0);
		free(line[i]);
	}
	free(line);
	return (list);
}

int	parse_readline(t_list *list, char *s)
{
	char **line;

	line = ft_split(s, ' ');
	free(s);
	if (!line)
		return (false);
	list = move_in_list(line, list);
	// printf("Jai quoi dans list ?\n%p\n", list->list);
	if (!list)
		return (false);
	tmp_print(list);
	return (true);
}
