/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 04:14:33 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/03 14:42:45 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		len;

	env = *ft_getall_env();
	len = len_tab(env);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = NULL;
	start = tab;
	while (env)
	{
		*tab = ft_strdup(env->env);
		tab++;
		env = env->next;
	}
	return (start);
}
