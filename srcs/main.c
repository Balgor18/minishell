/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:41:23 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/29 19:15:15 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Pas encore d'arret sur la boucle || voir quoi mettre
// rl_clear_history(); --> check le leaks

int	g_error;

int	main(int ac, char **av, char **env)
{
	char	*line;

	line = NULL;
	init_env(ac, av, env);
	while (1)
	{
		line = readline("Minishell rose : ");
		if (line == NULL)
			break ;
		add_history(line);
		if (line)
			shell_split(line);
	}
	delall_env();
	rl_clear_history();
	return (EXIT_SUCCESS);
}
