/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:12:55 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/05 18:49:04 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	error_parsing(char *word)
{
	g_error = 2;
	error_msg(ERROR_PARSING);
	write(STDERR_FILENO, " '", 2);
	ft_putstr_fd(STDERR_FILENO, word);
	write(STDERR_FILENO, "'", 1);
	write(STDERR_FILENO, "\n", 1);
}

int	verif_token(int actual, int last)
{
	if (last == HEREDOC && actual != LIMITOR)
		return (false);
	if ((last == R_OUT || last == APPEND) && actual != FD)
		return (false);
	if (actual == PIPE && (last == PIPE || last == R_IN
			|| last == APPEND || last == HEREDOC))
		return (false);
	if (actual == PIPE && last == -1)
		return (false);
	return (true);
}

static int	verif_last_token(int last, int actual)
{
	if ((last == PIPE || last == R_IN || last == R_OUT || last == APPEND
			|| last == HEREDOC) && actual == -1)
		return (false);
	return (true);
}

int	verif_parsing(t_node *list)
{
	t_node	*last;
	int		last_token;

	last_token = -1;
	last = list;
	while (list)
	{
		if (!verif_token(list->token, last_token))
		{
			error_parsing(list->word);
			return (false);
		}
		last_token = list->token;
		last = list;
		list = list->next;
	}
	if (!list)
		if (!verif_last_token(last_token, -1))
			return (error_parsing(last->word), false);
	return (true);
}
