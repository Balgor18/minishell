/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:24 by elaachac          #+#    #+#             */
/*   Updated: 2022/02/08 00:17:50 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] && s2[i]) && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
** ft_strchr(char *S, int C)
** This function research the char C in the string S
** if he found the char C in S return TRUE
** Or return FALSE if not found
*/
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

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size;
	char		*s2;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen((char *)s1);
	while (size && ft_strchr(set, s1[size - 1]))
		size--;
	s2 = ft_substr((char *)s1, 0, size);
	return (s2);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

//return NULL if error
//size[0] == LEN MAX OF EVERY *TAB
//size[1] == Get the return elem of ft_strlcpy

char	*ft_joinstr_from_tab(char **tab, int nb_word)
{
	char	*ret;
	int		w;
	size_t	size[2];

	w = ((size[1] = (size[0] = 0, 0), 0));
	while (w < nb_word)
	{
		if (tab[w])
			size[0] += ft_strlen(tab[w]);
		w++;
	}
	if (size[0] == 0)
		return (free_tab(tab), NULL);
	ret = malloc(sizeof(char *) * (size[0] + 1));
	if (!ret)
		return (free(tab), NULL);
	w = 0;
	while (w < nb_word)
	{
		if (tab[w])
			size[1] += ft_strlcpy(ret + size[1], tab[w], ft_strlen(tab[w]) + 1);
		free(tab[w]);
		w++;
	}
	return (free(tab), ret);
}
