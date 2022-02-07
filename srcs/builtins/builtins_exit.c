/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:50:06 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/07 19:47:58 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_exit(char *word)
{
	ft_putstr_fd(STDERR_FILENO, "Minishell: exit: ");
	ft_putstr_fd(STDERR_FILENO, word);
	ft_putstr_fd(STDERR_FILENO, " : numeric argument required\n");
	return (2);
}

static char	*remove_quote(char *s)
{
	int		nb_quote;
	char	*tmp;
	char	*bis;

	tmp = ((nb_quote = 0, s));
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			nb_quote++;
		s++;
	}
	s = tmp;
	tmp = malloc(sizeof(char) * (ft_strlen(s) - nb_quote));
	if (!tmp)
		return (NULL);
	bis = ((tmp[ft_strlen(s) - nb_quote] = '\0', tmp));
	while (*s)
	{
		if (*s != '\'' && *s != '"')
			tmp += ((*tmp = *s, 1));
		s++;
	}
	return (bis);
}

static int	str_is_digit(char **s)
{
	int		good;
	char	*tmp;

	good = false;
	tmp = *s;
	*s = remove_quote(*s);
	free(tmp);
	tmp = *s;
	while (*tmp)
	{
		if (ft_isdigit(*tmp))
			good = true;
		tmp++;
	}
	if (!good)
		return (false);
	return (true);
}

static int	len_list(t_node *list)
{
	int	ret;

	ret = 0;
	while (list)
	{
		ret++;
		list = list->next;
	}
	return (ret);
}

int	builtins_exit(t_node *list, t_cmd *cmd)
{
	int	exit_val;

	if (cmd->fd[IN] != STDIN_FILENO || cmd->fd[OUT] != STDOUT_FILENO)
		return (g_error = 0, true);
	exit_val = EXIT_SUCCESS;
	if (len_list(list) > 1)
		return (g_error = 1, ft_putstr_fd(STDERR_FILENO, ERROR_TO_MANY), true);
	if (list)
	{
		if (str_is_digit(&list->word))
			exit_val = ft_atoi(list->word);
		else
			exit_val = error_exit(list->word);
	}
	free_cmd(cmd);
	delall_env();
	rl_clear_history();
	exit(exit_val);
	return (g_error = 0, true);
}
