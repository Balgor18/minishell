/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:45:31 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/09 14:50:57 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_list *line)
{
	t_node	*tmp_node;
	size_t	lenght;

	lenght = line->lenght;
	tmp_node = line->head;
	while (lenght)
	{
		set_token(tmp_node);
		tmp_node = tmp_node->next;
		lenght--;
	}
}