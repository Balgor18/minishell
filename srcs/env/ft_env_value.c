/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 05:58:10 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/06 05:58:17 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_value(char *find)
{
	t_env	*env;

	if (!find)
		return (NULL);
	env = *ft_getall_env();
	while (env)
	{
		if (ft_strncmp(env->env, find, ft_strlen(find)) == 0)
		{
			while (*(env->env) != '=')
				env->env++;
			env->env++;
			return (env->env);
		}
		env = env->next;
	}
	return (NULL);
}
