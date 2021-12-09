/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:41:23 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/08 11:32:01 by fcatinau         ###   ########.fr       */
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
		line = readline( "Minishell rose >");
		// parse_line(line);
	}
	return (EXIT_SUCCESS);
}
