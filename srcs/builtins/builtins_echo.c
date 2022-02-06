/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:46:23 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/06 11:27:31 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_flag_n(char *word)
{
	if (!*word)
		return (true);
	while (*word)
	{
		if (*word != '-' && *word != 'n' && *word != ' ')
			return (false);
		word++;
	}
	return (true);
}

/*
** builtins_echo
** the function reproduce echo
** But i code it
** can work with the option -n
*/
int	builtins_echo(t_node *arg, int fd_out)
{
	int	endl;

	endl = true;
	if (!arg || !arg->word)
		return (write(fd_out, "\n", 1), true);
	while (verif_flag_n(arg->word))
	{
		endl = false;
		arg = arg->next;
	}
	while (arg)
	{
		ft_putstr_fd(fd_out, arg->word);
		arg = arg->next;
		if (arg)
			write(fd_out, " ", 1);
	}
	if (endl)
		write(fd_out, "\n", 1);
	return (g_error = 0, true);
}
