/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:50:06 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/03 16:55:05 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_exit(char *word)
{
	ft_putstr_fd(STDERR_FILENO, "Minishell: exit: ");
	ft_putstr_fd(STDERR_FILENO, word);
	ft_putstr_fd(STDERR_FILENO, " : numeric argument required\n");
	return (2);
}

static int	str_is_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int	builtins_exit(t_node *list, t_cmd *cmd)
{
	int	exit_val;

	exit_val = EXIT_SUCCESS;
	if (list)
	{
		if (str_is_digit(list->word))
			exit_val = ft_atoi(list->word);
		else
			exit_val = error_exit(list->word);
	}
	free_cmd(cmd);
	delall_env();
	rl_clear_history();
	exit(exit_val);
	return (g_error = 0, true);
}
