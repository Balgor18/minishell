/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 01:17:24 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/07 20:29:37 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

static int	expand_dollar_start(char *line)
{
	int	start;

	start = 0;
	while (line[start] == ' ')
		start++;
	return (start);
}

static int	expand_dollar_stop(int start, char *line)
{
	if (line[start])
		start++;
	while (ft_is_alpha(line[start]) || line[start] == '_')
		start++;
	return (start);
}

static int	expand_split_dollar_rec(char ***tab, char *line, int index)
{
	int	i[MAX_SPLIT];

	i[START] = expand_dollar_start(line);
	i[END] = expand_dollar_stop(i[START], line);
	if (i[END] > 0)
	{
		if (!expand_split_dollar_rec(tab, line + i[END], index + 1))
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

static void	tmp_print(char **tab)
{
	while (*tab)
	{
		dprintf(2, RED"|%s|\n"CYAN"--------\n"RESET, *tab);
		tab++;
	}
}

static void	expand_modif_tab_dollar(char **tab_dollar)
{
	char	*tmp;
	char	*env;

	while ((*tab_dollar))
	{
		if (ft_strlen((*tab_dollar)) > 1)
		{
			env = ft_env_value((*tab_dollar) + 1);
			if (!env)
			{
				tmp = malloc(sizeof(char) * 1);
				if (!tmp)
					return ;
				tmp[0] = '\0';
			}
			else
				tmp = ft_strdup(env);
			if (!tmp)
				return ;
			free(*tab_dollar);
			*tab_dollar = tmp;
		}
		tab_dollar++;
	}
}

void	expand_split_dollar(char **line)
{
	char	**tab_dollar;

	tab_dollar = NULL;
	expand_split_dollar_rec(&tab_dollar, *line, 0);
	if (tab_dollar)
		expand_modif_tab_dollar(tab_dollar);
	tmp_print(tab_dollar);
	free(*line);
	*line = ft_joinstr_from_tab(tab_dollar);
	return ;
}
