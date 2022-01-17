/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:23:51 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/17 22:20:13 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
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

void	free_list(t_node *list)
{
	t_node	*tmp;

	tmp = NULL;
	while (list)
	{
		tmp = list->next;
		free(list->word);
		free(list);
		list = tmp;
	}
	list = NULL;
}
