/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:41:23 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/03 17:27:49 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Pas encore d'arret sur la boucle || voir quoi mettre
// rl_clear_history(); --> check le leaks

// check for a singelton for env

int	g_error;

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argv;
	(void)env;
	line = NULL;
	g_error = 0;
	if (argc != 1)
		return (error_msg(NO_ARG));
	while (1)
	{
		line = readline("Minishell rose : ");
		if (line == NULL)
			break ;
		if (line)
			shell_split(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
