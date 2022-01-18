/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 22:54:23 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/18 22:10:01 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordcount(char const *str, char sep)
{
	int	i;
	int	count;

	if (str == 0 || str[0] == 0)
		return (0);
	i = 1;
	count = 0;
	if (str[0] != sep)
		count++;
	while (str[i] != '\0')
	{
		if (str[i] != sep && str[i - 1] == sep)
			count++;
		i++;
	}
	return (count);
}

static char	**ft_malloc(char const *str, char sep)
{
	int		len;
	char	**tab_str;

	len = ft_wordcount(str, sep);
	tab_str = malloc(sizeof(*tab_str) * (len + 1));
	if (tab_str == 0)
		return (0);
	return (tab_str);
}

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

// i[0] = i;
// i[1] = s;

char	**ft_split(char const *str, char charset)
{
	int			i[2];
	int			j;
	char		**tab_str;

	i[0] = -1;
	i[1] = 0;
	tab_str = ft_malloc(str, charset);
	if (!tab_str)
		return (0);
	while (++i[0] < ft_wordcount(str, charset))
	{
		j = 0;
		tab_str[i[0]] = malloc(ft_next_word_count(str, charset, i[1]) + 1);
		if (!tab_str[i[0]])
			return (ft_free(tab_str, i[0]));
		while (str[i[1]] != '\0' && str[i[1]] == charset)
			i[1]++;
		while (str[i[1]] != '\0' && str[i[1]] != charset)
			tab_str[i[0]][j++] = str[i[1]++];
		tab_str[i[0]][j] = '\0';
	}
	tab_str[i[0]] = 0;
	return (tab_str);
}
