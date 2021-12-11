/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:38:22 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/11 14:52:41 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Je viendrais te poser des questions car je vois pas ce que font les fonctions des listes chaines
t_list	*newlist(void)// pourquoi tu veux malloc la list ??
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(*newlist));
	if (newlist == NULL)
		return (NULL);
	if (newlist != NULL)
	{
		// newlist->lenght = 0;
		newlist->head = NULL;
		// newlist->tail = NULL;
	}
	return (newlist);
}

// void	dellist(t_list **list)
// {
// 	t_node	*tmp;
// 	t_node	*del;

// 	if (list != NULL)
// 	{
// 		tmp = (*list)->head;
// 		// while ((*list)->lenght > 0)
// 		{
// 			// (*list) ->lenght--;
// 			del = tmp;
// 			if (tmp->next)
// 				tmp = tmp->next;
// 			free(del);
// 		}
// 		free(*list);
// 		*list = NULL;
// 	}
// }


// t_node	*init_node(t_node *node, int token, char *word)
// {
// 	node->token = token;
// 	node->word = ft_strdup(word);
// 	return (node);
// }

t_node	*init_node(t_node *node, int token, char *word)
{
	node->token = token;
	node->word = ft_strdup(word);
	return (node);
}

// t_node	*add_tail_list(t_list **list, int token, char *word)
// {
// 	t_node	*newnode;
//
// 	newnode = (t_node *)malloc(sizeof(*newnode));
// 	if (!newnode)
// 		return (NULL);
// 	if ((*list) != NULL)
// 	{
// 		if ((*list)->tail == NULL)
// 		{
// 			(*list)->head = newnode;
// 			(*list)->tail = newnode;
// 			newnode->prev = NULL;
// 			newnode->next = NULL;
// 		}
// 		else
// 		{
// 			(*list)->tail->next = newnode;
// 			newnode->prev = (*list)->tail;
// 			(*list)->tail = newnode;
// 		}
// 		// (*list)->lenght++;
// 	}
// 	return (init_node(newnode, token, word));
// }

t_node	*ft_lstlast(t_list **list)
{
	while ((*list)->list)
	{
		if (!(*list)->list->next)
			return ((*list)->list);
		(*list)->list = (*list)->list->next;
	}
	return ((*list)->list);
}

void	add_back_list(t_list **list, t_node *new)
{
	t_node *tmp;

	if (!list)
		return ;
	(*list)->list = (*list)->list->next;
	if (*list == NULL)
		(*list)->list = new;
	else
	{
		tmp = ft_lstlast(list);
		tmp->next = new;
	}
}

t_node	*add_tail_list(t_list **list, int token, char *word)
{
	t_node	*new;

	new = malloc(sizeof(*new) * 1);
	if (!new)
		return (NULL);
	new = &(t_node) {0};
	if (!(*list)->head)
	{
		(*list)->head = new;
		(*list)->list = new;
	}
	else
	{
		add_back_list(list, new);
	}
	init_node(new, token, word);
	return (new);
}

