/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:38:22 by elaachac          #+#    #+#             */
/*   Updated: 2022/01/03 15:48:30 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_list	*newlist(void)
// {
// 	t_list	*newlist;

// 	newlist = (t_list *)malloc(sizeof(*newlist));
// 	if (newlist == NULL)
// 		return (NULL);
// 	if (newlist != NULL)
// 	{
// 		newlist->lenght = 0;
// 		newlist->head = NULL;
// 		newlist->tail = NULL;
// 	}
// 	return (newlist);
// }

// t_node	*delnode(t_node *node, t_list **list)
// {
// 	t_node	*tmp;

// 	tmp = NULL;
// 	if (node->next == node)
// 	{
// 		free(node);
// 		node = NULL;
// 	}
// 	else
// 	{
// 		tmp = node;
// 		node = tmp->next;
// 		tmp->prev->next = node;
// 		node->prev = tmp->prev;
// 		free(tmp);
// 	}
// 	(*list)->lenght--;
// 	return (node);
// }

// void	dellist(t_list **list)
// {
// 	t_node	*tmp;
// 	t_node	*del;

// 	if (list != NULL)
// 	{
// 		tmp = (*list)->head;
// 		while ((*list)->lenght > 0)
// 		{
// 			(*list)->lenght--;
// 			del = tmp;
// 			if (tmp->next)
// 				tmp = tmp->next;
// 			free(del->word);
// 			del->word = NULL;
// 			free(del);
// 			del = NULL;
// 		}
// 	}
// }

// t_node	*init_node(t_node *node, char *word, t_list *list)
// {
// 	node->token = 0;
// 	node->word = ft_strdup(word);
// 	node->list = list;
// 	return (node);
// }

// t_node	*add_tail_list(t_list **list, char *word)
// {
// 	t_node	*newnode;

// 	newnode = (t_node *)malloc(sizeof(*newnode));
// 	if (!newnode)
// 		return (NULL);
// 	if ((*list))
// 	{
// 		if ((*list)->head == NULL)
// 		{
// 			newnode->prev = NULL;
// 			newnode->next = NULL;
// 			(*list)->head = newnode;
// 			(*list)->tail = newnode;
// 		}
// 		else
// 		{
// 			newnode->prev = (*list)->tail;
// 			newnode->next = NULL;
// 			(*list)->tail->next = newnode;
// 			(*list)->tail = newnode;
// 		}
// 		(*list)->lenght++;
// 	}
// 	return (init_node(newnode, word, *list));
// }

static t_node	*ft_lstlast(t_node *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

// static void	ft_lstadd_back(t_node **alst, t_node *new)
// {
// 	t_node	*tmp;

// 	if (alst)
// 	{
// 		if (*alst == NULL)
// 			*alst = new;
// 		else
// 		{
// 			tmp = ft_lstlast(*(alst));
// 			tmp->next = new;
// 		}
// 	}
// }

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
		tmp->prev->next = (*node);
		(*node)->prev = tmp->prev;
		free(tmp);
	}
	// (*list)->lenght--;
	return ((*node));
}

t_node	*delall(t_node **node)
{
	t_node	*tmp;

	// while ((*node))
	// 	(*node) = (*node)->prev;
	while ((*node))
	{
		tmp = (*node);
		free((*node)->word);
		(*node) = tmp->next;
		free(tmp);
	}
	exit(124);
	// return ((*node));
	return (NULL);
}

t_node	*init_node(t_node *node, char *word)
{
	node->token = 0;
	node->word = ft_strdup(word);
	// exit(14);
	return (node);
}

t_node	*add_tail_list(t_node **node, char *word)
{
	t_node	*newnode;
	t_node	*last;

	last = ft_lstlast(*node);
	newnode = (t_node *)malloc(sizeof(*newnode));
	if (!newnode)
		return (NULL);
	if (node)
	{
		if ((*node) == NULL)
		{
			newnode->prev = NULL;
			newnode->next = NULL;
			(*node) = newnode;
		}
		else
		{
			newnode->prev = last;
			newnode->next = NULL;
			last->next = newnode;
		}
	}

	return (init_node(newnode, word));
}
