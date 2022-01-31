/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:37:33 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/31 17:19:55 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_end_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
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

static void	error_export(char *error)
{
	g_error = 1;
	ft_putstr_fd(STDERR_FILENO, ERROR_EXP_START);
	ft_putstr_fd(STDERR_FILENO, "`");
	ft_putstr_fd(STDERR_FILENO, error);
	ft_putstr_fd(STDERR_FILENO, "'");
	ft_putstr_fd(STDERR_FILENO, ERROR_EXP_END);
}

/*
** builtins_export
** add the new env
*/
int	builtins_export(t_node *arg)
{
	char	*ret;
	char	*cpy;

	cpy = arg->word;
	if (!ft_strchr(arg->word, '='))
		error_export(arg->next->word);
	while (*cpy != '=' && *cpy)
		cpy++;
	if (!*cpy)
		return (true);
	cpy++;
	cpy = ft_strdup(cpy);
	expand_remove_quote(&cpy);
	ret = trim_before_egals(arg->word);
	free(arg->word);
	arg->word = ft_strjoin(ret, cpy);
	free(ret);
	free(cpy);
	add_env(arg->word);
	return (true);
}
