/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_dollar_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:29:52 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/07 16:36:46 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_no_dollar_quote(t_node *list)
{
	char	**tab;
	char	**tab2;
	int		len_tab;

	expand_quote_split_rec(&tab, list->word, 0);
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
