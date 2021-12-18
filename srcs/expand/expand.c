/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:40:56 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/18 15:20:26 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//check expand

// create get_env(char *need_to_find, char **env)

// =============================
// word = ' '"$ < > | "' '
//
// =============================

// Check "ls<"

// export L="s -la"
// check comportement
// check l$L

// check how to do
// export test="a b c d e f"
// ls < $test

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

int	change_node(t_node *node, char **env)
{
	(void)node;
	(void)env;
	// do something
	printf("Need to change node\n");
	return (false);
}

// !! check si je men occupe ?
// quote[0] = No quote
// quote[1] = '
// quote[2] = "
int	check_word(t_node *node, char **env, int *quote)
{
	char	*tmp;

	tmp = node->word;
	(void)quote;
	while (*tmp)
	{
		if (is_special_char(*tmp, "<|>$"))
			if (change_node(node, env))
				return (false);
		tmp++;
	}
	return (true);
}

int	expand(t_list *list, char **env)
{
	t_node	*node;
	int		quote[3];

	quote[0] = 0;// init quote check if need -- probably not
	quote[1] = 0;
	quote[2] = 0;
	node = list->head;
	while (node)
	{
		check_word(node, env, quote);
		node = node->next;
	}
	return (true);
}
