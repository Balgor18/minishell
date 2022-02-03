/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:18:07 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/03 17:31:23 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_strjoin_add_slash
** join S1 and S2
** and add '/' between us
** return NULL if error
** else return malloc char
*/
char	*ft_strjoin_add_slash(char const *s1, char const *s2)
{
	int		i[3];
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i[1] = ft_strlen((char *)s1);
	i[2] = ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (i[1] + i[2] + 2));
	if (str == NULL)
		return (NULL);
	i[0] = -1;
	while (s1[++i[0]])
		str[i[0]] = s1[i[0]];
	i[0] = -1;
	str[i[1]++] = '/';
	while (s2[++i[0]])
	{
		str[i[1]] = s2[i[0]];
		i[1]++;
	}
	str[i[1]] = '\0';
	return (str);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*bis;

	while (cmd)
	{
		if (cmd->arg)
			delall(&cmd->arg);
		if (cmd->red)
			delall(&cmd->red);
		if (cmd->fd[IN] != 0)
			close(cmd->fd[IN]);
		if (cmd->fd[OUT] != 1)
			close(cmd->fd[OUT]);
		bis = cmd;
		cmd = bis->next;
		free(bis);
	}
}

int	create_heredoc(int type)
{
	int		ret;

	if (type)
	{
		ret = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (ret < 0)
			ret = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	else
	{
		ret = open("/tmp/.heredoc", O_RDONLY | O_CREAT, 0777);
		if (ret < 0)
			ret = open(".heredoc", O_RDONLY | O_CREAT, 0777);
	}
	return (ret);
}

/*
** list_len
** return the size of t_node
*/
static int	list_len(t_node *list)
{
	int	nb;

	nb = 0;
	while (list)
	{
		nb++;
		list = list->next;
	}
	return (nb);
}

/*
** exec_move_list_in_char
** get list in enter and create a char **
** with all word of list
*/
char	**exec_move_list_in_char(t_node *list)
{
	char	**ret;
	char	**tab;

	ret = malloc(sizeof(char *) * (list_len(list) + 1));
	if (!ret)
		return (NULL);
	ret[list_len(list)] = NULL;
	tab = ret;
	while (list)
	{
		*ret = ft_strdup(list->word);
		list = list->next;
		ret++;
	}
	return (tab);
}
