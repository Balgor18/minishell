/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 01:34:05 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/31 14:32:46 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtins_echo
** the function reproduce echo
** But i code it
** can work with the option -n
*/
static int	builtins_echo(t_node *arg)
{
	int	endl;

	endl = true;
	if (ft_strcmp("-n", arg->word))
	{
		endl = false;
		arg = arg->next;
	}
	while (arg)
	{
		ft_putstr_fd(STDOUT_FILENO, arg->word);
		arg = arg->next;
		if (arg)
				write(STDOUT_FILENO, " ", 1);
	}
	if (endl)
		write(STDOUT_FILENO, "\n", 1);
	return (true);
}

/*
** builtins_pwd
** Get the pwd in the env
** and print it in STDOUT
*/
static int	builtins_pwd(void)
{
	char	*ret;

	ret = ft_env_value("PWD");
	ft_putstr_fd(STDOUT_FILENO, ret);
	write(STDOUT_FILENO, "\n", 1);
	return (true);
}

/*
** builtins_export
** add the new env
*/
static int	builtins_unset(t_node *arg)// cmd
{
	delone_env(arg->word);
	return (true);
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
	return (true);
}

static int	builtins_exit(t_cmd *cmd)
{
	free_cmd(cmd);
	delall_env();
	exit(0);
	return (true);
}

/*
** Check builtins
** Return FALSE if is not a builtins
** return TRUE if found a builtins
*/
int	check_builtins(t_cmd *cmd)
{
	int	ret;

	ret = false;
	if (ft_strcmp(cmd->arg->word, "echo"))
		ret = builtins_echo(cmd->arg->next);
	else if (ft_strcmp(cmd->arg->word, "cd"))
		ret = builtins_cd(cmd->arg->next);
	else if (ft_strcmp(cmd->arg->word, "pwd"))
		ret = builtins_pwd();
	else if (ft_strcmp(cmd->arg->word, "export"))
		ret = builtins_export(cmd->arg->next);
	else if (ft_strcmp(cmd->arg->word, "unset"))
		ret = builtins_unset(cmd->arg->next);
	else if (ft_strcmp(cmd->arg->word, "env"))
		ret = builtins_env();
	else if (ft_strcmp(cmd->arg->word, "exit"))
		ret = builtins_exit(cmd);
	return (ret);
}
