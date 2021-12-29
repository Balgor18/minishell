/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:13:35 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/25 02:10:03 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *s)
{
	char	*t;

	t = s;
	while (*s)
		s++;
	return (s - t);
}

void	ft_putstr_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

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
