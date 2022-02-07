/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:37:33 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/07 19:05:24 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_end_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i + 1);
}

static char	*trim_before_egals(char *str)
{
	char	*ret;
	int		i[MAX_SPLIT];

	i[START] = 0;
	i[END] = trim_end_value(str);
	ret = ft_substr(str, i[START], i[END]);
	return (ret);
}

static void	var_exist(char *name)
{
	if (ft_env_value(name))
		delone_env(name);
}

static int	move_after_equals(char **cpy)
{
	while (*(*cpy) != '=' && *(*cpy))
		(*cpy)++;
	if (!*(*cpy))
		return (false);
	(*cpy)++;
	return (true);
}

/*
** builtins_export
** add the new env
*/
int	builtins_export(t_node *arg)
{
	char	*ret;
	char	*cpy;

	while (arg)
	{
		if (!arg)
			return (true);
		cpy = arg->word;
		if (!ft_strchr(arg->word, '='))
			return (true);
		if (ft_isdigit(*cpy))
			return (g_error = 1, error_export(cpy), true);
		if (!move_after_equals(&cpy))
			return (true);
		cpy = ft_strdup(cpy);
		// expand_remove_quote(&cpy);
		ret = trim_before_egals(arg->word);
		free(arg->word);
		var_exist(ret);
		arg->word = ft_strjoin(ret, cpy);
		free(ret);
		free(cpy);
		arg = ((add_env(arg->word), arg->next));
	}
	return (true);
}
