/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:46:23 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/03 17:07:35 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_flag_n(char *word)
{
	if (*word == '-')
		word++;
	while (*word && *word == 'n')
		word++;
	if (*word)
		return (false);
	return (true);
}

/*
** builtins_echo
** the function reproduce echo
** But i code it
** can work with the option -n
*/
int	builtins_echo(t_node *arg)
{
	int	endl;

	endl = true;
	if (arg)
	{
		if (verif_flag_n(arg->word))
		{
			endl = false;
			arg = arg->next;
		}
	}
	while (arg)
	{
		ft_putstr_fd(STDOUT_FILENO, arg->word);
		arg = arg->next;
		if (arg)
			write(STDOUT_FILENO, " ", 1);
	}
	if (endl)
		write(STDOUT_FILENO, "\n", 1);
	return (g_error = 0, true);
}
