/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:41:23 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/21 15:45:13 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	main4(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list *list;

	// list = (t_list **){0};
	list = (t_list *)malloc(sizeof(t_list));
	ft_bzero(list, sizeof(t_list));
	list->env = envp;
	add_tail_list(&list, WORD, argv[1]);
	if (argv[2])
		add_tail_list(&list, WORD, argv[2]);
	exec(list);
	dellist(&list);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_list	list;
	char	*line;

	(void)argv;
	(void)env;
	if (argc != 1)
		return (main4(argc, argv, env));	// incorporation du main de test pour l'exec
		// return (error_arg());
	while (1)// Pas encore d'arret sur la boucle || voir quoi mettre
	{
		list = (t_list){0};
		list.env = env;
		line = readline("Minishell rose :");
		if (line)
		{
			if (!parse_readline(&list, line))
				return (EXIT_FAILURE);
			if (!expand(&list, env))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
