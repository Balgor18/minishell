/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:47:52 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/13 16:44:45 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_fd(int *fd, t_node *iterator)
{
	if (iterator->token == R_IN)
	{
		if (file_exists(iterator->word) == true)
		{
			fd = open(argv[1], O_RDONLY);
		}
		else
		{
			//gestion d'erreur redir in inexistante
		}
	}
	else if (iterator->token == APPEND)
	{
		fd = open(iterator->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		fd = open(iterator->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
}
