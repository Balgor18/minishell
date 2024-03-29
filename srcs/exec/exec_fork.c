/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:02:24 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/08 14:47:26 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//reecrire les messages derreur
// pour .
// ./
// ..
static char	*try_open(char *cmd)
{
	int	ret;

	if (ft_strcmp(cmd, "."))
		return (ft_putstr_fd(STDERR_FILENO, ERROR_POINT), NULL);
	else if (ft_strcmp(cmd, ".."))
		return (ft_putstr_fd(STDERR_FILENO, ERROR_DOUBLE_POINT), NULL);
	else if (ft_strcmp(cmd, "./"))
		return (ft_putstr_fd(STDERR_FILENO, ERROR_POINT_SLASH), NULL);
	ret = access(cmd, X_OK);
	if (ret >= 0)
		return (ft_strdup(cmd));
	return (g_error = 126, perror(cmd), NULL);
}

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
		return (try_open(cmd));
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
		path = NULL;
		tab++;
	}
	free_tab(tab2);
	return (check_is_not_builtins(path, cmd));
}

static void	free_all(char **env, char **cmd_tab, char *path)
{
	if (path)
	{
		perror(path);
		free(path);
	}
	free_tab(env);
	free_tab(cmd_tab);
	delall_env();
}

static void	exec_fork_child(t_cmd *cmd, t_cmd *start)
{
	char	**cmd_tab;
	char	**env;
	char	*path;

	cmd_tab = ((env = env_to_tab(), exec_move_list_in_char(cmd->arg)));
	if (cmd->fd[IN] != STDIN_FILENO)
	{
		dup2(cmd->fd[IN], STDIN_FILENO);
		close(cmd->fd[IN]);
	}
	if (cmd->fd[OUT] != STDOUT_FILENO)
	{
		dup2(cmd->fd[OUT], STDOUT_FILENO);
		close(cmd->fd[OUT]);
	}
	path = find_cmd_path(cmd->arg->word);
	free_cmd(start);
	if (path)
	{
		init_signal(true);
		execve(path, cmd_tab, env);
	}
	free_all(env, cmd_tab, path);
	exit(g_error);
}

void	exec_fork(t_cmd *cmd, t_cmd *start)
{
	pid_t	pid;

	g_error = 0;
	if (!cmd->arg->word)
		return ;
	pid = fork();
	if (pid == -1)
		printf("Error fork on cmd = %s\n", cmd->arg->word);
	else if (pid == 0)
		exec_fork_child(cmd, start);
	else
		cmd->pid = pid;
}
