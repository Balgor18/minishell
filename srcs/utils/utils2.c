/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:24 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/16 15:15:03 by elaachac         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
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

char	*get_pwd()
{
	char	BUFFER[4096];
	char	*pwd;

	pwd = getcwd(BUFFER, 4096);
	return (pwd);
}
