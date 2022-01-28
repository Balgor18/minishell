/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:02:24 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/28 05:12:32 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_add_slash(char const *s1, char const *s2)
{
	int		i[3];
	char	*str;

	if (s1 && s2)
	{
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
	return (NULL);
}

static char	*find_cmd_path(char *cmd)// if not found path return NULL
{
	char	**tab2;
	char	**tab;
	char	*path;
	int		ret;

	path = ft_env_value("PATH");
	tab = ft_split(path, ':');
	tab2 = tab;
	while (*tab)
	{
		path = ft_strjoin_add_slash(*tab, cmd);
		ret = open(path, O_RDONLY);
		if (ret > 0)
		{
			close(ret);
			break ;
		}
		path = NULL;
		free(*tab);
		tab++;
	}
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab2);
	return (path);
}

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

char	**exec_move_list_in_char(t_node *list)
{
	char	**ret;
	char	**tab;

	ret = malloc(sizeof(char *) * (list_len(list) + 1));
	if (!ret)
		return (NULL);
	// printf("list_len %d\n", list_len(list));
	ret[list_len(list)] = NULL;
	// printf("list->word = %s\n", list->word);
	tab = ret;
	while (list)
	{
		*ret = list->word;
		list = list->next;
		ret++;
	}
	// printf("tab[0] = %s\n", tab[0]);
	// printf("tab[1] = %s\n", tab[1]);
	return (tab);
}

// do a function in env for change the type of env
static void	exec_fork_child(t_cmd *cmd)
{
	char	**cmd_tab;
	char	*path;
	char	**env;

	path = find_cmd_path(cmd->arg->word);// access
	if (!path)
		g_error = 127;
	cmd_tab = exec_move_list_in_char(cmd->arg);
	env = env_to_tab();
	if (cmd->fd[OUT] != 1)
	{
		dup2(cmd->fd[OUT], STDOUT_FILENO);
		close(cmd->fd[OUT]);
	}

	// dup2(cmd->fd[IN], STDIN_FILENO);
	// dup2(cmd->fd[OUT], STDOUT_FILENO);
	printf("g_Error %d\n", g_error);
	printf("fd[IN] = %d fd[OUT] = %d\n", cmd->fd[IN], cmd->fd[OUT]);
	printf("path = %s\n", path);
	printf("cmd_tab[0] = %s\ncmd_tab[1] = %s\n", cmd_tab[0], cmd_tab[1]);
	execve(path, cmd_tab, env);
	printf("Do a error\n");
	exit(1);
}

void	exec_fork(t_cmd **cmd)// modif cmd->arg in char **
{
	pid_t	pid;
	t_cmd	*cpy;

	pid = fork();
	// if (pid == -1)
		//do error
	if (pid == 0)
		exec_fork_child(*cmd);
	else
	{
		cpy = *cmd;
		*cmd = (*cmd)->next;
		free_list(cpy->arg);
		free_list(cpy->red);
		close(cpy->fd[IN]);
		close(cpy->fd[OUT]);
		free(cpy);
	}

}
