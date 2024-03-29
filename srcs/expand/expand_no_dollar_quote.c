/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_dollar_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:29:52 by fcatinau          #+#    #+#             */
/*   Updated: 2022/03/17 21:29:31 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_no_dollar_quote(t_node *list)
{
	char	**tab;
	char	**tab2;
	int		len_tab;

	if (!expand_quote_split_rec(&tab, list->word, 0))
		return ;
	len_tab = ft_strlen_tab(tab);
	free(list->word);
	tab2 = tab;
	while (*tab)
	{
		expand_remove_quote(tab);
		tab++;
	}
	list->word = ft_joinstr_from_tab(tab2, len_tab);
}

char	**only_one_line(char *line)
{
	char	**tab;

	tab = NULL;
	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[1] = NULL;
	tab[0] = ft_strdup(line);
	return (tab);
}
