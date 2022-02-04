/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:33:41 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/04 01:52:16 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pwd_old_pwd(void)
{
	static const char	oldpwd[9] = "OLDPWD=\0";
	static const char	pwd[5] = "PWD=\0";
	char				*pw;
	char				*opw;
	char				*tmp;

	opw = ft_env_value("PWD");
	pw = getcwd(NULL, 0);
	if (!pw)
		return (g_error = 127, (void)error_msg("getcwd fail\n"));
	tmp = pw;
	pw = ft_strjoin(pwd, pw);
	free(tmp);
	opw = ft_strjoin(oldpwd, opw);
	delone_env("OLDPWD");
	add_env(opw);
	free(opw);
	delone_env("PWD");
	add_env(pw);
	free(pw);
}

static void	cd_less(void)
{
	char	*ret;

	ret = ft_env_value("OLDPWD");
	if (!ret)
	{
		g_error = 1;
		printf("minishell: cd: OLDPWD not set\n");
	}
	else
	{
		chdir(ret);
		ft_putstr_fd(STDOUT_FILENO, ret);
		write(STDOUT_FILENO, "\n", 1);
		pwd_old_pwd();
	}
}

/*
** Create_pwd
** if PWD not exist a create it
*/
static void	create_pwd(void)
{
	static const char	pwd[5] = "PWD=\0";
	char				*pw;
	char				*tmp;

	pw = getcwd(NULL, 0);
	tmp = pw;
	pw = ft_strjoin(pwd, pw);
	free(tmp);
	add_env(pw);
	free(pw);
}

/*
** builtins_cd
** the function reproduce cd
** Work with relative path
** or aboslut path
** i recode the flag -
*/
int	builtins_cd(t_node	*arg)
{
	char	*ret;

	ret = NULL;
	if (!arg)
		return (g_error = 1, error_msg(ERROR_ARG_CD), true);
	if (!ft_env_value("PWD"))
		create_pwd();
	if (ft_strcmp("-", arg->word))
		cd_less();
	else
	{
		if (chdir(arg->word) == -1)
		{
			g_error = 1;
			perror(ret);
		}
		pwd_old_pwd();
	}
	return (g_error = 0, true);
}
