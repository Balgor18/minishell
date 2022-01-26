/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:47:21 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/26 18:37:11 by fcatinau         ###   ########.fr       */
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

static char	*exec_dollar_split(char *word)
{
	char	**tab_dollar;
	int		nb_word;

	expand_dollar_split_rec(&tab_dollar, word, 0);
	nb_word = ft_strlen_tab(tab_dollar);
	expand_modif_dollar_line(tab_dollar, nb_word);
	free(word);
	word = NULL;
	word = ft_joinstr_from_tab(tab_dollar, nb_word);
	tab_dollar = NULL;
	return (word);
}

static int	heredoc_expand(t_node *red)
{
	char	*limit;
	char	*line;
	int		fd;

	fd = create_heredoc(1);
	if (fd < 0)
		return (fd);
	if (red->next->token == LIMITOR)
		limit = red->next->word;
	while (get_next_line(0, &line, 0) > 0)
	{
		if (ft_strcmp(line, limit))
			break ;
		if (ft_strchr(line, '$'))
			line = exec_dollar_split(line);
		if (line)
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	return (fd);
}

static int	heredoc_no_expand(t_node *red)
{
	char	*limit;
	char	*line;
	int		fd;

	fd = create_heredoc(1);
	if (fd < 0)
		return (fd);
	if (red->next->token == LIMITOR)
		limit = red->next->word;
	while (get_next_line(0, &line, 0) > 0)
	{
		if (ft_strcmp(line, limit))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	return (fd);
}

int	exec_redir_heredoc(t_cmd *cmd)
{
	int	fd;

	fd = check_quote_limitor(cmd->red);
	if (fd)
		fd = heredoc_no_expand(cmd->red);
	else
		fd = heredoc_expand(cmd->red);
	close(fd);
	fd = create_heredoc(0);
	if (cmd->fd[IN] != 0)
		close(cmd->fd[IN]);
	cmd->fd[IN] = fd;
	return (true);
}
