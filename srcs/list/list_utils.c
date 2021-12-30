/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:38:22 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/30 14:45:19 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*newlist(void)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(*newlist));
	if (newlist == NULL)
		return (NULL);
	if (newlist != NULL)
	{
		newlist->lenght = 0;
		newlist->head = NULL;
		newlist->tail = NULL;
	}
	return (newlist);
}

t_node	*delnode(t_node *node, t_list **list)
{
	t_node	*tmp;

	tmp = NULL;
	if (node->next == node)
	{
		free(node);
		node = NULL;
	}
	else
	{
		tmp = node;
		node = tmp->next;
		tmp->prev->next = node;
		node->prev = tmp->prev;
		free(tmp);
	}
	(*list)->lenght--;
	return (node);
}

void	dellist(t_list **list)
{
	t_node	*tmp;
	t_node	*del;

	if (list != NULL)
	{
		tmp = (*list)->head;
		while ((*list)->lenght > 0)
		{
			(*list)->lenght--;
			del = tmp;
			if (tmp->next)
				tmp = tmp->next;
			free(del->word);
			del->word = NULL;
			free(del);
			del = NULL;
		}
	}
}

t_node	*init_node(t_node *node, char *word, t_list *list)
{
	node->token = 0;
	node->word = ft_strdup(word);
	node->list = list;
	return (node);
}

t_node	*add_tail_list(t_list **list, char *word)
{
	t_node	*newnode;

	newnode = (t_node *)malloc(sizeof(*newnode));
	if (!newnode)
		return (NULL);
	if ((*list))
	{
		if ((*list)->head == NULL)
		{
			newnode->prev = NULL;
			newnode->next = NULL;
			(*list)->head = newnode;
			(*list)->tail = newnode;
		}
		else
		{
			newnode->prev = (*list)->tail;
			newnode->next = NULL;
			(*list)->tail->next = newnode;
			(*list)->tail = newnode;
		}
		(*list)->lenght++;
	}
	return (init_node(newnode, word, *list));
}
