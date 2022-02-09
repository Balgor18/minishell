/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:04:20 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/09 18:50:39 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modif_shlvl(void)
{
	static const char	str[7] = "SHLVL=\0";
	char				*shlvl;
	char				*tmp;
	int					lvl;

	shlvl = ft_env_value("SHLVL");
	if (!shlvl)
		return ;
	lvl = ft_atoi(shlvl);
	delone_env("SHLVL");
	lvl++;
	tmp = ft_itoa(lvl);
	shlvl = ft_strjoin(str, tmp);
	free(tmp);
	add_env(shlvl);
	free(shlvl);
}
