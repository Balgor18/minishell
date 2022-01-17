/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:13:35 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/17 15:32:41 by fcatinau         ###   ########.fr       */
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

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (*tab)
	{
		i++;
		tab++;
	}
	return (i);
}

void	ft_putstr_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

int	error_msg(char *s)
{
	ft_putstr_fd(STDERR_FILENO, RED"Error\n"RESET);
	ft_putstr_fd(STDERR_FILENO, s);
	return (false);
}
