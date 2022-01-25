/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:47:21 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/25 12:04:07 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This function return true if quote is found
** or False if not found quote
*/

static int	check_quote_limitor(t_node *red)
{
	while (red)
	{
		if (red->token == LIMITOR)
		{
			if (!ft_strchr(red->word, '\'') && !ft_strchr(red->word, '"'))
				return (false);
		}
		red = red->next;
	}
	return (true);
}

// static void	heredoc_no_expand(t_node *red)
// {
// 	char	*limit;
// 	char	*line;
	
// 	while ()//use gnl
// 	{
// 		if (ft_strcmp(line, limit))
// 			break ;
// 		// do something
// 	}
	
// }

// static void	heredoc_expand(t_node *red)
// {
// 	char	*limit;
// 	char	*line;
	
// 	while ()//use gnl
// 	{
// 		if (ft_strcmp(line, limit))
// 			break ;
// 		// do something
// 	}
	
// }

void	exec_redir_heredoc(t_cmd *cmd)
{
	int	ret;

	ret = check_quote_limitor(cmd->red);
	dprintf(2, "ret quote limitor = %d\n", ret);
	// if (ret)
		// heredoc without expand
	// else
		// heredoc with expand
}