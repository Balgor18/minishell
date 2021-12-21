/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/21 19:22:10 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// good WORD = Si ses pas autre choses ses un mot
//      FD = always after < > << >> |
// good LIMITOR = Cat du HDOC le mot apres et le limiteur || voir si autre cas
// good R_IN = Redirection in donc <
// good HDOC (HEREDOC)= Redirection << [LIMITEUR]
// good R_OUT = redirection out donc >
// good APPEND = >>
// good PIPE = |

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

char	*spc_prev_in_list(t_list *list, int *token, char *start, char *stop);
char	*spc_next_in_list(t_list *list, int *token, char *start, char *stop);

char	*do_special_in_list(t_list *list, int *token, char *last, char *s)
{
	//test< test
	//< test
	if (is_special_char(*s, "'\""))
		s = spc_quote_in_list(list, token, last, s);
	else if (is_special_char(*s, "<|>"))
	{
		if (*(s - 1) == ' ' && *(s + 1) == ' ')
			s = spc_rd_in_list(list, token, last, s);
		else if (*(s - 1) == ' ')
		{
			printf(RED"next \n"WHITE);
			s = spc_next_in_list(list, token, last, s);
		}
		else if (*(s + 1) == ' ')// work
		{
			s = spc_prev_in_list(list, token, last, s);
		}
	}
	if (*s == ' ')
		return (s + 1);
	return (s);
}

// echo  "test    "
// test
// ls /etc

// if (is_special_char(*s, "'\""))
// 	s = spc_quote_in_list(list, &token, last, s);
// else if (is_special_char(*s, "<|>"))
// 	s = spc_rd_in_list(list, &token, last, s);

// test<<lol|get_yolo>>okmec

// ls < cat
// ls<cat

// check to add in list what is behind

int	parse_readline(t_list *list, char *s, char *free_word)
{
	int		token;
	char	*last;

	token = WORD;
	last = s;
	while (*s)
	{
		if (is_special_char(*s, "'\"<|>"))
		{
			s = do_special_in_list(list, &token, last, s);
			last = s;
			if (*s == ' ')
				last = s + 1;
		}
		else if (*s == ' ' && *s + 1 != '\0')
		{
			word_in_list(list, check_token(s, token), last, s);
			token = check_token(s, token);
			last = s + 1;
		}
		s++;
	}
	// if (s != last)
	// printf("last == |%s|\n%p\ns = |%s|\n%p\n", last, last, s, s);
	word_in_list(list, check_token(s, token), last, s);
	free(free_word);
	tmp_print(list);
	return (true);
}

// test a faire

// echo salut a tous
// echo "salut a tous" // pas bon
// echo 'salut a tous' // pas bon

// test test

// ls < cat
// ls <cat
// ls< cat // pas bon
// ls<cat // pas bon

// echo "Salut a tous"|yolo > cd

//ech"o" "a"
//ech"o"" a"
