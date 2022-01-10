/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 00:18:50 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/10 14:52:29 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_single_quote(char **tab)
{
	char	*tmp;

	tmp = ft_strtrim((*tab), "'");
	free((*tab));
	(*tab) = tmp;
}

static int	expand_double_and_no_quote(char **tab, int quote)
{
	char	*tmp;
	// char**	split_shell;

	if (quote == DOUBLE)
	{
		tmp = ft_strtrim((*tab), "\"");
		if (!tmp)
			return (false);
		free((*tab));
		(*tab) = tmp;
	}
	if (ft_strchr(*tab, '$'))
		expand_split_dollar(tab);
	if (tab && quote == NO_QUOTE)// check for create new function and add elem to list but probably not in this function
	{
		// function space -1
		// shell_split_rec(&split_shell, *tab, 0);
		// tmp_print(split_shell);
		// push_tab_in_list(&list, split_shell);
	}
	return (true);
}

void	expand_modif_tab(char **tab)
{
	while (*tab)
	{
		if ((*tab)[0] == '\'')
			expand_single_quote(tab);
		else if ((*tab)[0] == '"')
			expand_double_and_no_quote(tab, DOUBLE);
		else
			expand_double_and_no_quote(tab, NO_QUOTE);
		tab++;
	}
}
