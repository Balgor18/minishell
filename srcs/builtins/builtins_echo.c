/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:46:23 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/02 18:23:58 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strcmp("-n", arg->word))
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
