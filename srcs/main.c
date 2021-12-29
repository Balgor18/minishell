/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:41:23 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/28 15:09:52 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

// Pas encore d'arret sur la boucle || voir quoi mettre
// rl_clear_history(); --> check le leaks

int	main(int argc, char **argv, char **env)
{
	t_list	list;
	char	*line;

	(void)argv;
	(void)env;
	if (argc != 1)
		return (error_arg());
	while (1)
	{
		list = (t_list){0};
		line = readline("Minishell rose :");
		if (line)
		{
			if (!parse_readline(&list, line, line))
			{
				rl_clear_history();
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
