/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:46:17 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/13 16:47:33 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	file_check(char *path)
{
	if (access(path, F_OK) == -1)
	{
		perror(path);
		return (false);
	}
	else
		return (true);
}
