/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:18:42 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/08 15:35:38 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote_heredoc(char **s)
{
	char	*test;

	test = NULL;
	test = ft_strtrim(*s, "\"'");
	free(*s);
	*s = test;
}
