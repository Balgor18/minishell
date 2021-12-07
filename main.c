/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:41:23 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/07 17:10:06 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	main(int argc, char **argv)// check si message d'erreur quand plusieur ARG
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)g_error;
	while (1)// Pas encore d'arret sur la boucle || voir quoi mettre
	{
		line = NULL;
		printf( "%s\n", readline( "test> " ) );
		// parse_line(line);
	}
	return (EXIT_SUCCESS);
}
