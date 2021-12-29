/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:05:31 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/29 16:01:03 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tmp_print(t_list *list)
{
	t_node	*node;

	node = list->head;
	while (node)
	{
		printf("world = |%s|\ntoken = %d\n-------\n", node->word, node->token);
		node = node->next;
	}
}

static void	free_tab(char ***tab)
{
	char	**free_tab;

	free_tab = *tab;
	if ((*tab))
	{
		while (*(*tab))
		{
			if (*(*tab))
			{
				free(*(*tab));
				*(*tab) = NULL;
			}
			(*tab)++;
		}
	}
	free(free_tab);
	free_tab = NULL;
}

static int	push_tab_in_list(t_list *list, char **tab)
{
	char	**free_tab;

	free_tab = tab;
	while (*tab)
	{
		if (!add_tail_list(&list, *tab))
		{
			dellist(&list);
			return (false);
		}
		free(*tab);
		tab++;
	}
	if (free_tab)
		free(free_tab);
	return (true);
}

int	shell_split_rec(char ***tab, char *line, int index)
{
	int	i[MAX_SPLIT];
	int	ret;

	i[START] = split_start_word(line);
	i[END] = split_end_word(line, i[START]);
	if (i[END] > 0)
	{
		if (line[i[END]] == ' ')
			ret = shell_split_rec(tab, line + i[END] + 1, index + 1);
		else
			ret = shell_split_rec(tab, line + i[END], index + 1);
		if (!ret)
			return (false);
		(*tab)[index] = ft_substr(line, i[START], i[END] - i[START]);
		if (!(*tab)[index])
			return (false);
	}
	else if (i[END] == 0)
	{
		(*tab) = (char **)malloc(sizeof(char *) * index + 1);
		if (!(*tab))
			return (false);
		(*tab)[index] = NULL;
	}
	return (true);
}

int	shell_split(t_list *list, char ***tab, char *line)
{
	if (!shell_split_rec(tab, line, 0))
	{
		free_tab(tab);
		return (false);
	}
	if (!push_tab_in_list(list, *tab))
	{
		free_tab(tab);
		return (false);
	}
	return (true);
}

int	parse_readline(t_list *list, char *s)
{
	char	**split;

	if (!shell_split(list, &split, s))
	{
		free(s);
		return (false);
	}
	free(s);
	tokeniser(list);
	tmp_print(list);
	return (true);
}
