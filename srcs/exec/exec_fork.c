/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:02:24 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/01 18:50:22 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** find_cmd_path
** find in all env the path of the cmd
** return malloc line with the path and tje cmd
** return NULL if found nothing
*/
static char	*find_cmd_path(char *cmd)
{
	char	**tab2;
	char	**tab;
	char	*path;
	int		ret;

	if (*cmd == '.' || *cmd == '/')
		return (cmd);
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
		free(path);
		tab++;
	}
	free_tab(tab2);
	return (path);
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

static void	exec_fork_child(t_cmd *cmd, t_cmd *start, char *path)
{
	char	**cmd_tab;
	char	**env;

	cmd_tab = exec_move_list_in_char(cmd->arg);
	env = env_to_tab();
	if (cmd->fd[IN] != 0)
	{
		dup2(cmd->fd[IN], STDIN_FILENO);
		printf("fd[IN] = %d\n", cmd->fd[IN]);
		close(cmd->fd[IN]);
	}
	if (cmd->fd[OUT] != 1)
	{
		dup2(cmd->fd[OUT], STDOUT_FILENO);
		printf("fd[OUT] = %d\n", cmd->fd[OUT]);
		close(cmd->fd[OUT]);
	}
	init_signal(true);
	free_cmd(start);
	execve(path, cmd_tab, env);
	exit(1);
}

void	exec_fork(t_cmd *cmd, t_cmd *start)
{
	pid_t	pid;
	char	*path;

	path = ((g_error = 0, find_cmd_path(cmd->arg->word)));
	if (!path)
	{
		g_error = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
		printf("Error fork on cmd = %s\n", cmd->arg->word);
	else if (pid == 0)
		exec_fork_child(cmd, start, path);
	else
	{
		cmd->pid = pid;
		free(path);
	}
}
