/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:38:22 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/05 16:42:50 by elaachac         ###   ########.fr       */
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
	if (node->next && node->next == node)
	{
		free(node->word);
		(*list)->lenght--;
		free(node);
		node = NULL;
	}
	else
	{
		tmp = node;
		if (node->prev == NULL)
		{
			if (tmp->next != NULL)
				node->next->prev = NULL;
		}
		else if (node->next == NULL)
		{
			if (tmp->prev != NULL)
				node->prev->next = NULL;
		}
		else
		{
			tmp->next->prev = node->prev;
			tmp->prev->next = node->next;
		}
		if (tmp->prev)
			node = tmp->prev;
		free(tmp->word);
		tmp->word = NULL;
		(*list)->lenght--;
		free(tmp);
		tmp = NULL;
	}
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
			del = tmp;
			if (tmp->next)
				tmp = tmp->next;
			delnode(del, &del->list);
		}
		free(*list);
		*list = NULL;
	}
}

t_node	*init_node(t_node *node, int token, char *word, t_list *list)
{
	node->token = token;
	node->word = ft_strdup(word);
	node->list = list;
	return (node);
}

t_node	*add_tail_list(t_list **list, int token, char *word)
{
	t_node	*newnode;

	newnode = (t_node *)malloc(sizeof(*newnode));
	if (!newnode)
		return (NULL);
	if ((*list) != NULL)
	{
		if ((*list)->head == NULL)
		{
			(*list)->head = newnode;
			(*list)->tail = newnode;
			newnode->prev = NULL;
			newnode->next = NULL;
		}
		else
		{
			(*list)->tail->next = newnode;
			newnode->prev = (*list)->tail;
			newnode->next = NULL;
			(*list)->tail = newnode;
		}
		(*list)->lenght++;
	}
	return (init_node(newnode, token, word, *list));
}
