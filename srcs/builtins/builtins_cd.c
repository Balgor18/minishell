/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:33:41 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/30 17:15:48 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** change_pwd
** change the env value of PWD and OLDPWD
*/
static void	change_pwd(t_node *arg)
{
	static const char	oldpwd[9] = "OLDPWD=\0";
	static const char	pwd[5] = "PWD=\0";
	char				*ret;
	char				*tmp;

	delone_env("OLDPWD");
	ret = ft_strjoin(oldpwd, ft_env_value("PWD"));
	add_env(ret);
	if ((ft_env_value("PWD")[ft_strlen(ft_env_value("PWD"))]) == '/')
		ret = ft_strjoin(ft_env_value("PWD"), arg->word);
	else
		ret = ft_strjoin_add_slash(ft_env_value("PWD"), arg->word);
	delone_env("PWD");
	tmp = ret;
	ret = ft_strjoin(pwd, ret);
	free(tmp);
	add_env(ret);
}

static void	change_pwd_double_point(t_node *arg)
{
	// static const char	oldpwd[9] = "OLDPWD=\0";
	// static const char	pwd[5] = "PWD=\0";
	// char				*ret;
	// char				*tmp;
	(void)arg;
	printf("%s\n", getcwd(ft_env_value("PWD"), 0));
	// delone_env("OLDPWD");
	// ret = ft_strjoin(oldpwd, ft_env_value("PWD"));
	// add_env(ret);
	// if ((ft_env_value("PWD")[ft_strlen(ft_env_value("PWD"))]) == '/')
	// 	ret = ft_strjoin(ft_env_value("PWD"), arg->word);
	// else
	// 	ret = ft_strjoin_add_slash(ft_env_value("PWD"), arg->word);
	// delone_env("PWD");
	// tmp = ret;
	// ret = ft_strjoin(pwd, ret);
	// free(tmp);
	// add_env(ret);
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
	if (ft_strcmp("-", arg->word))
	{
		ret = ft_env_value("OLDPWD");
		if (!ret)
			printf("minishell: cd: OLDPWD not set\n");
		else
			chdir(ret);
	}
	else
	{
		if (chdir(arg->word) == -1)
			perror(ret);
		else if (ft_strcmp("..", arg->word))
			change_pwd_double_point(arg);
		else
			change_pwd(arg);
	}
	return (true);
}
