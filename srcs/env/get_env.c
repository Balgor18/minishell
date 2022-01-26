/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 19:19:53 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/26 21:50:57 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_env(env, NULL, NULL);
}

void	add_env(char *add)
{
	ft_env(NULL, add, NULL);
}

void	delone_env(char *del)
{
	ft_env(NULL, NULL, del);
}

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
		free(tmp);
	}
}

t_env	**ft_getall_env(void)
{
	return (ft_env(NULL, NULL, NULL));
}

static int	len_tab(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_tab(void)
{
	char	**start;
	char	**tab;
	t_env	*env;

	env = *ft_getall_env();
	tab = malloc(sizeof(char *) * (len_tab(env) + 1));
	if (!tab)
		return (NULL);
	tab[len_tab(env)] = NULL;
	start = tab;
	while (env)
	{
		*tab = env->env;
		env = env->next;
	}
	return (start);
}
