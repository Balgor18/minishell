/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:13:35 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/14 13:45:46 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_arg(void)
{
	ft_putstr_fd(STDERR_FILENO, RED"Error\n"WHITE"Minishell don't need arg\n");
	return (EXIT_FAILURE);
}

int	error_filename(void)
{
	ft_putstr_fd(STDERR_FILENO, RED"Error\n"WHITE"error filename after redir -> function to do\n");
	return (EXIT_FAILURE);
}
