/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 19:19:53 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/30 20:58:34 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** init_env
** function cast in void AC and AV
** But fill my env of minishell
*/
void	init_env(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_env(env, NULL, NULL);
}

/*
** add_env
** add the string ADD to env
*/
void	add_env(char *add)
{
	ft_env(NULL, add, NULL);
}

/*
** delone_env
** del the string DEL to env
*/
void	delone_env(char *del)
{
	ft_env(NULL, NULL, del);
}

/*
** delall_env
** del all the env
*/
void	delall_env(void)
{
	t_env	*tmp;
	t_env	*env;

	tmp = NULL;
	env = *ft_getall_env();
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->env);
		free(tmp);
	}
}

/*
** ft_getall_env
** Function return all the env of the project
*/
t_env	**ft_getall_env(void)
{
	return (ft_env(NULL, NULL, NULL));
}
