/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:21:07 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/14 19:19:57 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

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

static void	expand_modif_dollar_line(char **tab)
{
	char	*tmp;
	char	*env;

	while ((*tab))
	{
		if (ft_strlen((*tab)) > 1 && ft_strchr(*tab, '$'))
		{
			// $? !!!
			env = ft_env_value((*tab) + 1);
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
			free(*tab);
			*tab = tmp;
		}
		tab++;
	}
}

static void	expand_space_neg(char *line)
{
	if (!*line)
		return ;
	while (*line)
	{
		if (*line == ' ')
			*line *= -1;
		line++;
	}
}

void	tmp_print_tab(char **tab)
{
	while (*tab)
	{
		printf("*tab = %s\n",*tab);
		tab++;
	}
}

void	expand_dollar_split(char **tab_quote)
{
	char	**print;
	char	**tab_dollar;
	int		ret;
	int		turn;

	turn = 0;
	print = tab_quote;
	tab_dollar = NULL;
	// printf(GREEN"Start\n"RESET);
	// tmp_print_tab(print);
	while (*tab_quote)
	{
		turn ++;
		ret = expand_remove_quote(tab_quote);
		if (ret != SIMPLE)
		{
			expand_dollar_split_rec(&tab_dollar, *tab_quote, 0);
			expand_modif_dollar_line(tab_dollar);
			free(*tab_quote);
			*tab_quote = NULL;
			*tab_quote = ft_joinstr_from_tab(tab_dollar);
			if (ret == DOUBLE && *tab_quote)
				expand_space_neg(*tab_quote);
		}
		// printf("%d %s\n", turn, *tab_quote);
		// tmp_print_tab(print);
		tab_quote++;
	}
	// printf("---------------\n");
	// tmp_print_tab(print);
	// printf(RED"End\n"RESET);
	// exit(125);
	return ;
}
