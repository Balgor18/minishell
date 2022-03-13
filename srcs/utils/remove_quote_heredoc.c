/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:18:42 by fcatinau          #+#    #+#             */
/*   Updated: 2022/03/13 22:07:57 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote_heredoc(char **s)
{
	char	**tab;
	int		nb_word;
	int		i;

	i = -1;
	expand_quote_split_rec(&tab, *s, 0);
	free(*s);
	nb_word = ft_strlen_tab(tab);
	while (++i < nb_word)
		expand_remove_quote(&tab[i]);
	*s = ft_joinstr_from_tab(tab, nb_word);
	if (!*s)
		*s = NULL;
}
