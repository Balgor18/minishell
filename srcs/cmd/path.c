/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:40:13 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/15 18:11:20 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_check2(int cmd_ok, char **env_path, char *pathname, t_cmd *cmd)
{
	if (cmd_ok == 0)
	{
		free_split(env_path);
		if (cmd->file_error == 0 || cmd->file_error == 2)
		{
			write(2, pathname, ft_strlen(pathname));
			write(2, " : Command not found\n", 21);
			// cmd->error = 1; // ->gestion d'erreur
		}
		return (1);
	}
	else
		free_split(env_path);
	return (0);
}

void	cmd_check3(int i, int *cmd_ok, char **env_path, t_cmd *cmd)
{
	while (--i)
	{
		if (access(env_path[i], F_OK) != -1)
		{
			cmd->cmd_path[cmd->index] = ft_strdup(env_path[i]);
			cmd->index++;
			*cmd_ok = 1;
			break ;
		}
	}
}

int	find_path(char *pathname, t_cmd *cmd)
{
	char	**env_path;
	char	*tmp;
	int		i;
	int		cmd_ok;

	// cmd->error = 0; //-> globale error
	i = -1;
	cmd_ok = 0;
	tmp = NULL;
	env_path = NULL;
	env_path = ft_split(cmd->env_path, ':');
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		free(env_path[i]);
		env_path[i] = NULL;
		env_path[i] = ft_strjoin(tmp, pathname);
		free(tmp);
	}
	cmd_check3(i, &cmd_ok, env_path, cmd);
	return (cmd_check2(cmd_ok, env_path, pathname, cmd));
}
