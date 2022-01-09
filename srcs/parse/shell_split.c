/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/07 20:27:48 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	push_tab_in_list(t_node **list, char **tab)
{
	if (!tab)
		return (false);
	while (*tab)
	{
		if (!add_tail_list(list, *tab))
		{
			delall(list);
			return (false);
		}
		tab++;
	}
	return (true);
}

static int	shell_split_rec(char ***tab, char *line, int index)
{
	int	i[MAX_SPLIT];

	i[START] = split_start_word(line);
	i[END] = split_end_word(line, i[START]);
	if (i[END] > 0)
	{
		if (!shell_split_rec(tab, line + i[END], index + 1))
			return (false);
		(*tab)[index] = ft_substr(line, i[START], i[END] - i[START]);
		if (!(*tab)[index])
			return (false);
	}
	else if (i[END] == 0)
	{
		(*tab) = (char **)malloc(sizeof(char *) * (index + 1));
		if (!(*tab))
			return (false);
		(*tab)[index] = NULL;
	}
	return (true);
}

static void	free_tab(char **tab)
{
	char	**free_tab;

	if (!tab)
		return ;
	free_tab = tab;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(free_tab);
	return ;
}

void	shell_split(char *line)
{
	t_node	*node;
	char	**tab;

	tab = NULL;
	node = NULL;
	shell_split_rec(&tab, line, 0);
	push_tab_in_list(&node, tab);
	free_tab(tab);
	if (node)
		tokeniser(node);
	delall(&node);
	dprintf(2, RED"g_error = %d\n"RESET, g_error);// have to remove
	if (g_error == 0) // have to remove
		delall(&node);
	return ;
}
