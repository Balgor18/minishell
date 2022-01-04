/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:12:55 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/04 13:33:28 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_parsing(char *word)
{
	error_msg(ERROR_PARSING);
	write(STDERR_FILENO, " '", 2);
	ft_putstr_fd(STDERR_FILENO, word);
	write(STDERR_FILENO, "'", 1);
	write(STDERR_FILENO, "\n", 1);
}

// good WORD = Si ses pas autre choses ses un mot
// good FD = always after < > >>
// good LIMITOR = Cat du HEREDOC le mot apres et le limit|| voir si autre cas
// good R_IN = Redirection in donc <
// good HEREDOC (HEREDOC)= Redirection << [LIMITEUR]
// good R_OUT = redirection out donc >
// good APPEND = >>
// good PIPE = |

// enum e_token
// {
// 	WORD = 0,// mot
// 	FD = 1, // operateur
// 	LIMITOR = 2, // operateur
// 	R_IN = 3, // operateur
// 	HEREDOC = 4, // operateur
// 	R_OUT = 5, // operateur
// 	APPEND = 6, // operateur
// 	PIPE = 7, // operateur // check if pipe do a error
// };

// if not a word
// and if double same operateur

int	verif_token(int actual, int last)
{
	if (last == HEREDOC && actual != LIMITOR)
		return (false);
	if ((last == R_IN || last == R_OUT || last == APPEND) && actual != FD)
		return (false);
	if (last == PIPE && actual == PIPE)
		return (false);
	return (true);
}

// syntax error --> print line of syntax ??
int	verif_parsing(t_node *list)
{
	int		last_token;

	last_token = -1;
	while (list)
	{
		if (!verif_token(list->token, last_token))
		{
			g_error = 2;
			error_parsing(list->word);
			return (false);
		}
		last_token = list->token;
		list = list->next;
	}
	return (true);
}
