/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:38:22 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/04 21:26:30 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*ft_node_last(t_node *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_node	*delnode(t_node **node)
{
	t_node	*tmp;

	tmp = NULL;
	if ((*node)->next == (*node))
	{
		free(node);
		(*node) = NULL;
	}
	else
	{
		tmp = (*node);
		(*node) = tmp->next;
		free(tmp);
	}
	return ((*node));
}

t_node	*delall(t_node **node)
{
	t_node	*tmp;

	while ((*node))
	{
		tmp = (*node);
		free((*node)->word);
		(*node) = (*node)->next;
		free(tmp);
	}
	node = NULL;
	return (NULL);
}

t_node	*init_node(t_node *node, char *word)
{
	node->token = 0;
	node->word = ft_strdup(word);
	return (node);
}

t_node	*add_tail_list(t_node **node, char *word)
{
	t_node	*newnode;
	t_node	*last;

	last = ft_node_last(*node);
	newnode = (t_node *)malloc(sizeof(*newnode));
	if (!newnode)
		return (NULL);
	if (node)
	{
		if ((*node) == NULL)
		{
			newnode->next = NULL;
			(*node) = newnode;
		}
		else
		{
			newnode->next = NULL;
			last->next = newnode;
		}
	}
	return (init_node(newnode, word));
}
