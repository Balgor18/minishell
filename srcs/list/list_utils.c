/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:38:22 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/21 14:47:31 by elaachac         ###   ########.fr       */
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
		free(node);
		node = NULL;
	}
	else
	{
		tmp = node;
		if (tmp->next)
			node = tmp->next;
		if(tmp->prev)
			if (tmp->prev->next)
				tmp->prev->next = node;
		if (tmp->prev)
			node->prev = tmp->prev;
		free(tmp->word);
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
		while ((*list)->list)
		{
			(*list)->lenght--;
			del = tmp;
			if (tmp->next)
				tmp = tmp->next;
			free(del);
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
