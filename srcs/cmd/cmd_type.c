/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:32 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/14 17:28:44 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == true || ft_strcmp(cmd, "cd") == true || \
		ft_strcmp(cmd, "pwd") == true || ft_strcmp(cmd, "export") == true || \
		ft_strcmp(cmd, "unset") == true || ft_strcmp(cmd, "env") == true || \
		ft_strcmp(cmd, "exit") == true)
		return (true);
	else
		return (false);
}
