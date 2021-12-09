/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:14:52 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/10 00:15:03 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_next_word_count(char const *str, char sep, int i)
{
	int	count;

	count = 0;
	while (str[i] == sep && str[i] != '\0')
		i++;
	while (str[i] != '\0' && str[i] != sep)
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **str_tab, int i)
{
	int	j;

	j = 0;
	while (j < i && str_tab[j] != 0)
	{
		free(str_tab[j]);
		j++;
	}
	free(str_tab);
	return (0);
}

char	**ft_split(char const *str, char charset)
{
	int			s;
	static int	i = -1;
	int			j;
	char		**tab_str;

	if (str == 0)
		return (0);
	s = 0;
	tab_str = ft_malloc(str, charset);
	if (!tab_str)
		return (0);
	while (++i < ft_wordcount(str, charset))
	{
		j = 0;
		tab_str[i] = malloc(ft_next_word_count(str, charset, s) + 1);
		if (!tab_str[i])
			return (ft_free(tab_str, i));
		while (str[s] != '\0' && str[s] == charset)
			s++;
		while (str[s] != '\0' && str[s] != charset)
			tab_str[i][j++] = str[s++];
		tab_str[i][j] = '\0';
	}
	tab_str[i] = 0;
	return (tab_str);
}
