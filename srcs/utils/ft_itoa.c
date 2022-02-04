/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:38:19 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/17 14:38:46 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	itoa_negative(int *n, int *negative, int *len)
{
	*negative = 0;
	if (*n < 0)
	{
		*n *= -1;
		*negative = 1;
	}
	len += *negative;
}

static int	ft_len(int tmp)
{
	int	len;

	len = 2;
	while (tmp > 10)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		nega;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 2;
	itoa_negative(&n, &nega, &len);
	len = ft_len(n);
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (nega)
		str[0] = '-';
	return (str);
}
