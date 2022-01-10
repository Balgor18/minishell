/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:52:04 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/10 22:55:27 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	expand_single_quote(char **line)
// {
// 	char	*tmp;
	
// 	tmp = NULL;
// 	tmp = ft_strtrim(*line, "'");
// 	if (!tmp)
// 		return ;
// 	free(*line);
// 	*line = tmp;
// }

// static void	expand_modif_line(char **line)
// {
// 	printf("Modif line = %s\n", *line);
// 	if (*(*line) == '\'')
// 		expand_single_quote(line);
// 	// else if (*line == '"')
// 	// 	// function for double_quote
// 	// else
// 	// 	//function for no_quote
// 	printf("Modif line = %s\n", *line);
// }

void	expand_find_dollar(char **tab)// lets see if we need to return t_node
{
	char	**free_tab;

	free_tab = tab;
	while (*tab)
	{
		if (ft_strchr(*tab, '$'))
			expand_dollar_split(tab);// call a other split
			// expand_modif_line(tab);
		// free(*tab);
		dprintf(2, "LINE = %s\n", *tab);
		tab++;
	}
	// free(free_tab);
}
