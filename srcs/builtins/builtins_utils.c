/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:35:59 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/04 09:07:06 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_is_not_builtins(char *path, char *cmd)
{
	if (ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "pwd")
		|| ft_strcmp(cmd, "export") || ft_strcmp(cmd, "unset")
		|| ft_strcmp(cmd, "env") || ft_strcmp(cmd, "exit"))
	{
		if (path)
			free(path);
		return (ft_strdup(cmd));
	}
	if (!path)
		return (error_cmd(cmd), path);
	return (path);
}
