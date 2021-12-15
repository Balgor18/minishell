/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:24 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/15 15:03:55 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strchr(const char *s, int c)
{
	if ((char)c == '\0')
		return (false);
	while (*s)
	{
		if (*s == (char)c)
			return (true);
		s++;
	}
	return (false);
}

char	*get_env_var(char **envp, char *to_find)
{
	char	**env;

	env = envp;
	while (*env != 0)
	{
		if (ft_strncmp(*env, to_find, 4) == 0)
			return (*env);
		env++;
	}
	return (NULL);
}
