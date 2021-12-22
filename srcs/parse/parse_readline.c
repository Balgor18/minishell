/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/22 18:26:34 by fcatinau         ###   ########.fr       */
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

// echo  "test    "
// test
// ls /etc

// if (is_special_char(*s, "'\""))
// 	s = spc_quote_in_list(list, &token, last, s);
// else if (is_special_char(*s, "<|>"))
// 	s = spc_rd_in_list(list, &token, last, s);

// si j'utilise les index alors pas besoin de free_word
int	parse_readline(t_list *list, char *s, char *free_word)
{
	char	**split;

	shell_split(&split, s);
	free(free_word);
	// tokeniser();
	tmp_print(list);
	return (true);
}

// test a faire

// test<<lol|get_yolo>>okmec

// ls < cat
// ls<cat

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
