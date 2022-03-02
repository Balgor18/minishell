/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:47:05 by fcatinau          #+#    #+#             */
/*   Updated: 2022/03/02 14:02:33 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_unset(char *s)
{
	while (*s)
	{
		if (!ft_is_alpha(*s) && !ft_isdigit(*s) && *s != '_')
			return (false);
		s++;
	}
	return (true);
}

/*
** builtins_export
** add the new env
*/
int	builtins_unset(t_node *arg)
{
	while (arg)
	{
		if (!verif_unset(arg->word))
			error_unset(arg->word);
		else
			delone_env(arg->word);
		arg = arg->next;
	}
	return (g_error = 0, true);
}
