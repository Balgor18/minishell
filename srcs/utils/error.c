/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:13:35 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/09 23:35:09 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_arg(void)
{
	ft_putstr_fd(STDERR, RED"Error\n"WHITE"Minishell don't need arg\n");
	return (EXIT_FAILURE);
}
