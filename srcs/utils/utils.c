/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:48:08 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/10 00:14:36 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *s)
{
	char	*t;

	t = s;
	while (*s)
		s++;
	return (s - t);
}

void	ft_putstr_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = ((char *)malloc(sizeof(char) * (ft_strlen(s1) + 1)));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static int	ft_wordcount(char const *str, char sep)
{
	int	i;
	int	count;

	if (str == 0 || str[0] == 0)
		return (0);
	i = 1;
	count = 0;
	if (str[0] != sep)
		count++;
	while (str[i] != '\0')
	{
		if (str[i] != sep && str[i - 1] == sep)
			count++;
		i++;
	}
	return (count);
}

static char	**ft_malloc(char const *str, char sep)
{
	int		len;
	char	**tab_str;

	len = ft_wordcount(str, sep);
	tab_str = malloc(sizeof(*tab_str) * (len + 1));
	if (tab_str == 0)
		return (0);
	return (tab_str);
}
