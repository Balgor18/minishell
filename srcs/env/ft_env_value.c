/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 05:58:10 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/08 00:43:21 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_before_equals(char *env, char *find)
{
	if (!find)
		return (false);
	while (*find && *env && *env != '=' && *env == *find)
	{
		env++;
		find++;
	}
	if (*env == '=' && !*find)
		return (true);
	return (false);
}

/*
** ft_env_value
** Search the value of find in env
** return pointer of string after '='
** return NULL if not found
*/
char	*ft_env_value(char *find)
{
	t_env	*env;
	char	*tmp;

	if (!find)
		return (NULL);
	env = *ft_getall_env();
	while (env)
	{
		if (compare_before_equals(env->env, find))
		{
			tmp = env->env;
			while (*tmp != '=')
				tmp++;
			tmp++;
			return (tmp);
		}
		env = env->next;
	}
	return (NULL);
}
