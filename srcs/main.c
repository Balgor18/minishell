/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:41:23 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/10 00:10:20 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	main(int argc, char **argv, char **env)// check si message d'erreur quand plusieur ARG
{
	t_list	list;
	char	*line;

	list = (t_list) {0};
	(void)argv;
	(void)env;
	if (argc != 1)
		return (error_arg());
	while (1)// Pas encore d'arret sur la boucle || voir quoi mettre
	{
		line = readline("Minishell rose >");
		parse_readline(line);
	}
	return (EXIT_SUCCESS);
}
