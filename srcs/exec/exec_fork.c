/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:02:24 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/26 23:26:20 by fcatinau         ###   ########.fr       */
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

	path = ft_env_value("PATH");
	tab = ft_split(path, ':');
	tab2 = tab;
	while (*tab)
	{
		path = ft_strjoin_add_slash(*tab, cmd);
		if (open(path, O_RDONLY) > 0)
			break ;
		free(*tab);
		tab++;
	}
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab2);
	printf("find path = %s\n", path);
	return (path);
}

// do a function in env for change the type of env
static void	exec_fork_child(char **cmd, char *path, char **env)
{
	execve(path, cmd, env);
	// execve();//lets see if execve free all the infos
	return ;
}

// static void	exec_fork_parent()
// {

// }

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
		*ret = list->word;
		list = list->next;
		ret++;
	}
	return (tab);
}

void	exec_fork(t_cmd *cmd)// modif cmd->arg in char **
{
	pid_t	pid;
	char	**cmd_tab;
	char	*path;
	char	**env;

	path = find_cmd_path(cmd->arg->word);// need while on arg
	if (!path)
		g_error = 127;
	cmd_tab = exec_move_list_in_char(cmd->arg);
	env = env_to_tab();

	pid = fork();
	if (!pid)
		exec_fork_child(cmd_tab, path, env);
	// else
	// 	exec_fork_parent();
}
