/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 01:34:05 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/03 17:33:45 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtins_pwd
** Get the pwd in the env
** and print it in STDOUT
*/
static int	builtins_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (!ret)
		return (g_error = 127, error_msg("getcwd fail\n"), true);
	ft_putstr_fd(STDOUT_FILENO, ret);
	write(STDOUT_FILENO, "\n", 1);
	free(ret);
	return (g_error = 0, true);
}

/*
** builtins_export
** add the new env
*/
static int	builtins_unset(t_node *arg)
{
	if (arg)
		delone_env(arg->word);
	return (g_error = 0, true);
}

/*
** builtins_env
** Get env and print it al env in STDOUT
*/
static int	builtins_env(void)
{
	t_env	*env;

	env = *ft_getall_env();
	while (env)
	{
		ft_putstr_fd(STDOUT_FILENO, env->env);
		write(STDOUT_FILENO, "\n", 1);
		env = env->next;
	}
	return (g_error = 0, true);
}

/*
** Check builtins
** Return FALSE if is not a builtins
** return TRUE if found a builtins
*/
int	check_builtins(char *path, t_cmd *cmd)
{
	int	ret;

	ret = false;
	if (ft_strcmp(path, "echo"))
		ret = builtins_echo(cmd->arg->next);
	else if (ft_strcmp(path, "cd"))
		ret = builtins_cd(cmd->arg->next);
	else if (ft_strcmp(path, "pwd"))
		ret = builtins_pwd();
	else if (ft_strcmp(path, "export"))
		ret = builtins_export(cmd->arg->next);
	else if (ft_strcmp(path, "unset"))
		ret = builtins_unset(cmd->arg->next);
	else if (ft_strcmp(path, "env"))
		ret = builtins_env();
	else if (ft_strcmp(path, "exit"))
		ret = builtins_exit(cmd->arg->next, cmd);
	return (ret);
}
