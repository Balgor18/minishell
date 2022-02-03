/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:02:36 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/03 20:33:25 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cmd(char *cmd)
{
	g_error = 127;
	ft_putstr_fd(STDERR_FILENO, "Minishell :");
	ft_putstr_fd(STDERR_FILENO, cmd);
	ft_putstr_fd(STDERR_FILENO, ERROR_CMD);
}

void	error_sig(void)
{
	if (g_error == 128 + SIGTERM)
		ft_putstr_fd(STDERR_FILENO, "Terminated\n");
	else if (g_error == 128 + SIGSEGV)
		ft_putstr_fd(STDERR_FILENO, "Segmentation fault (core dumped)\n");
	else if (g_error == 128 + SIGQUIT)
		ft_putstr_fd(STDERR_FILENO, "Quit (core dumped)\n");
	else if (g_error == 128 + SIGABRT)
		ft_putstr_fd(STDERR_FILENO, "Aborted (core dumped)\n");
}

void	error_export(char *error)
{
	g_error = 1;
	ft_putstr_fd(STDERR_FILENO, ERROR_EXP_START);
	ft_putstr_fd(STDERR_FILENO, "`");
	ft_putstr_fd(STDERR_FILENO, error);
	ft_putstr_fd(STDERR_FILENO, "'");
	ft_putstr_fd(STDERR_FILENO, ERROR_EXP_END);
}
