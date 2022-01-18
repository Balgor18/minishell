/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:21:07 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/18 22:35:55 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_start(char *line)
{
	int	start;

	start = 0;
	while (line[start] == ' ')
		start++;
	return (start);
}

static int	expand_stop(int start, char *line)
{
	if (line[start] == '$')
	{
		start++;
		while (ft_is_alpha(line[start]) || line[start] == '_')
			start++;
	}
	else
		while (line[start] != '$' && line[start])
			start++;
	return (start);
}

static int	expand_dollar_split_rec(char ***tab, char *line, int index)
{
	int	i[MAX_SPLIT];

	i[START] = expand_start(line);
	i[END] = expand_stop(i[START], line);
	if (i[END] > 0)
	{
		if (!expand_dollar_split_rec(tab, line + i[END], index + 1))
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

static void	expand_modif_dollar_line(char **tab, int nb_word)
{
	int		word;
	char	*tmp;
	char	*env;

	word = 0;
	while (word < nb_word)
	{
		if (ft_strlen((tab[word])) > 1 && ft_strchr(tab[word], '$'))
		{
			if ((tab[word])[1] == '?')
				env = ft_itoa(g_error);
			else
				env = ft_env_value((tab[word]) + 1);
			if (!env)
				tmp = NULL;
			else
			{
				tmp = ft_strdup(env);
				if (!tmp)
					return ;
			}
			tab[word] = (free(tab[word]), tmp);
		}
		word++;
	}
}

char	**expand_dollar_split(char **tab_quote, char **tab)
{
	char	**tab_dollar;
	int		ret;
	int		nb_word;

	tab_dollar = NULL;
	while (*tab_quote)
	{
		ret = expand_remove_quote(tab_quote);
		if (ret != SIMPLE)
		{
			expand_dollar_split_rec(&tab_dollar, *tab_quote, 0);
			nb_word = ft_strlen_tab(tab_dollar);
			expand_modif_dollar_line(tab_dollar, nb_word);
			free(*tab_quote);
			*tab_quote = NULL;
			*tab_quote = ft_joinstr_from_tab(tab_dollar, nb_word);
			if (ret == DOUBLE && *tab_quote)
				expand_space_neg(*tab_quote);
			tab_dollar = NULL;
		}
		tab_quote++;
	}
	return (tab);
}
