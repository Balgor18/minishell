/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:33:41 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/01 11:57:11 by fcatinau         ###   ########.fr       */
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
	free(ret);
	if ((ft_env_value("PWD")[ft_strlen(ft_env_value("PWD"))]) == '/')
		ret = ft_strjoin(ft_env_value("PWD"), arg->word);
	else
		ret = ft_strjoin_add_slash(ft_env_value("PWD"), arg->word);
	delone_env("PWD");
	tmp = ret;
	ret = ft_strjoin(pwd, ret);
	free(tmp);
	add_env(ret);
	free(ret);
}

static size_t	get_end_of_pwd(char *test)
{
	char	*end;

	end = &test[ft_strlen(test)];
	end--;
	if (*end == '/')
		end--;
	while (*end != '/' && ft_is_alpha(*end + 1))
		end--;
	return (ft_strlen(end));
}

static void	change_pwd_double_point(void)
{
	static const char	oldpwd[9] = "OLDPWD=\0";
	static const char	pwd[5] = "PWD=\0";
	char				*str;
	char				*tmp;
	size_t				ret;

	str = NULL;
	delone_env("OLDPWD");
	str = ft_strjoin(oldpwd, ft_env_value("PWD"));
	add_env(str);
	free(str);
	ret = get_end_of_pwd(ft_env_value("PWD"));
	str = ft_substr(ft_env_value("PWD"), 0,
			ft_strlen(ft_env_value("PWD")) - ret);
	delone_env("PWD");
	tmp = str;
	str = ft_strjoin(pwd, str);
	free(tmp);
	add_env(str);
	free(str);
}

static void	swap_pwd_old_pwd(void)
{
	static const char	oldpwd[9] = "OLDPWD=\0";
	static const char	pwd[5] = "PWD=\0";
	char				*pw;
	char				*opw;

	pw = ft_env_value("PWD");
	opw = ft_env_value("OLDPWD");
	pw = ft_strjoin(oldpwd, pw);
	delone_env("PWD");
	opw = ft_strjoin(pwd, opw);
	delone_env("OLDPWD");
	add_env(pw);
	free(pw);
	add_env(opw);
	free(opw);
}

/*
** builtins_cd
** the function reproduce cd
** Work with relative path
** or aboslut path
** i recode the flag -
*/
int	builtins_cd(t_node	*arg, char *ret)
{
	if (!arg)
		return (true);
	if (ft_strcmp("-", arg->word))
	{
		ret = ft_env_value("OLDPWD");
		if (!ret)
			printf("minishell: cd: OLDPWD not set\n");
		else
		{
			chdir(ret);
			swap_pwd_old_pwd();
		}
	}
	else
	{
		if (chdir(arg->word) == -1)
			perror(ret);
		else if (ft_strcmp("..", arg->word))
			change_pwd_double_point();
		else
			change_pwd(arg);
	}
	return (true);
}
