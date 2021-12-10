/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:14:52 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/10 18:58:49 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

static void	*ft_strfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return ((void *)0);
}

static int	ft_nbwrds(char const *s, char c)
{
	int	i;
	int	j;

	if (!s)
		return (-1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (j);
}

static int	w(char const *s, int i, char c)
{
	while (s[i] != c && s[i])
		i++;
	return (i + 1);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		i[3];

	out = (char **)malloc(sizeof(char *) * (ft_nbwrds(s, c) + 1));
	if ((ft_nbwrds(s, c) == -1) || !(out))
		return (NULL);
	ft_bzero(i, 3 * sizeof(int));
	while (s[i[0]])
	{
		if (s[i[0]] != c)
		{
			out[i[1]] = (char *)malloc(sizeof(char) * w(s, i[0], c));
			if (!(out[i[1]]))
				return (ft_strfree(out));
			i[2] = 0;
			while (s[i[0]] != c && s[i[0]])
				out[i[1]][i[2]++] = s[i[0]++];
			out[i[1]][i[2]] = '\0';
			i[1]++;
		}
		else
			i[0]++;
	}
	out[i[1]] = NULL;
	return (out);
}
