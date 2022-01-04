/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:56:16 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/04 22:48:21 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_env_last(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static t_env	*ft_push_add_back(t_env *env, char *add)
{
	t_env	*new;

	if (!env)
	{
		env = malloc(sizeof(*env) * 1);
		if (!env)
			return (NULL);
		env->next = NULL;
		env->env = add;
		return (env);
	}
	else
	{
		new = malloc(sizeof(*env) * 1);
		if (!new)
			return (NULL);
	}
	ft_env_last(env)->next = new;
	new->env = add;
	new->next = NULL;
	return (env);
}

static t_env	*ft_env_create(char **env)
{
	t_env	*list;

	list = NULL;
	while (*env)
	{
		list = ft_push_add_back(list, *env);
		if (!list)
			return (NULL);
		env++;
	}
	return (list);
}

static t_env	*ft_env_delone(t_env *env, char *del)
{
	t_env	*next;
	t_env	*prev;
	t_env	*start;

	start = env;
	prev = env;
	while (env)
	{
		if (ft_strncmp(del, env->env, ft_strlen(del)) == 0)
		{
			next = env->next;
			free(env);
			prev->next = next;
			break ;
		}
		prev = env;
		env = env->next;
	}
	return (start);
}

t_env	**ft_env(char **env, char *add, char *del)
{
	static t_env	*list = NULL;

	if (env)
		list = ft_env_create(env);
	else if (add)
		list = ft_push_add_back(list, add);
	else if (del)
		list = ft_env_delone(list, del);
	return (&list);
}
