/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:14:58 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/25 14:25:12 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelall(t_gnl **lst)
{
	t_gnl	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
	}
}

int	ft_lstaddnew_front(struct s_data *data)
{
	t_gnl	*new_elem;

	new_elem = malloc(sizeof(t_gnl));
	if (!new_elem)
	{
		data->error = E_MALLOC_FAIL;
		return (0);
	}
	*new_elem = (t_gnl){0};
	new_elem->next = data->gnl;
	data->gnl = new_elem;
	return (1);
}

void	ft_cpy_buffer_list_free(t_gnl **gnl, char *line, size_t le_py)
{
	t_gnl	*tmp;

	if (*(*gnl)->buf == '\0' && (le_py % BUFF_SIZE) != 0)
	{
		tmp = (*gnl)->next;
		free(*gnl);
		*gnl = tmp;
	}
	if (*gnl)
	{
		ft_memcpy(line - (le_py % BUFF_SIZE), (*gnl)->buf, le_py % BUFF_SIZE);
		line -= le_py % BUFF_SIZE;
		tmp = (*gnl)->next;
		free(*gnl);
		*gnl = tmp;
	}
	while (*gnl)
	{
		ft_memcpy(line - BUFF_SIZE, (*gnl)->buf, BUFF_SIZE);
		line -= BUFF_SIZE;
		tmp = (*gnl)->next;
		free(*gnl);
		*gnl = tmp;
	}
	free(*gnl);
}

int	ft_no_newline_in_rest(struct s_data *data, struct s_mem *rest, char **line)
{
	data->ptrchr = ft_memchr(rest->str, '\n', rest->size);
	if (!data->ptrchr && rest->status)
		return (1);
	else if (data->ptrchr)
		data->line_size = data->ptrchr - rest->str;
	else
	{
		data->line_size = rest->size;
		return (1);
	}
	*line = malloc(sizeof(char) * (data->line_size + 1));
	if (!*line)
	{
		data->error = E_MALLOC_FAIL;
		return (-1);
	}
	ft_memcpy(*line, rest->str, data->line_size);
	(*line)[data->line_size] = '\0';
	rest->size = rest->size - data->line_size - 1;
	ft_memmove(rest->str, rest->str + data->line_size + 1, rest->size);
	return (0);
}
