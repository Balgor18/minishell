/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:46:23 by fcatinau          #+#    #+#             */
/*   Updated: 2022/03/17 21:23:33 by fcatinau         ###   ########.fr       */
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
	if (!arg)
		return (write(fd_out, "\n", 1), true);
	if (!arg->word || !arg->next)
		return (write(fd_out, "\n", 1), true);
	while (arg->word && verif_flag_n(arg->word))
	{
		endl = false;
		arg = arg->next;
	}
	while (arg)
	{
		if (arg->word)
			ft_putstr_fd(fd_out, arg->word);
		arg = arg->next;
		if (arg)
			write(fd_out, " ", 1);
	}
	if (endl)
		write(fd_out, "\n", 1);
	return (g_error = 0, true);
}
