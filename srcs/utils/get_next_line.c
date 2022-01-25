/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/25 14:21:09 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_no_buffer_in_read(struct s_data *data, struct s_mem *rest, int fd)
{
	int	ret;

	ret = read(fd, data->gnl->buf, BUFF_SIZE);
	if (ret == -1)
	{
		data->error = E_READ_FAIL;
		return (-1);
	}
	else if (ret > 0)
		data->rd_size = ret;
	else if (ret == 0)
	{
		data->rd_size = 0;
		rest->status = 1;
		if (data->list_size || rest->size)
			return (1);
		return (0);
	}
	return (data->rd_size);
}

int	ft_newline_bis(struct s_data *data, struct s_mem *rest, char **line)
{
	data->line_size = data->list_size + (data->ptrchr - data->gnl->buf);
	data->line_size += rest->size;
	*line = malloc(sizeof(char) * (data->line_size + 1));
	if (!*line)
	{
		data->error = E_MALLOC_FAIL;
		return (-1);
	}
	ft_memcpy(*line, rest->str, rest->size);
	(*line)[data->line_size] = '\0';
	ft_memcpy(rest->str, data->ptrchr + 1,
		data->rd_size - (data->ptrchr - data->gnl->buf) - 1);
	rest->size = data->rd_size - (data->ptrchr - data->gnl->buf) - 1;
	rest->str[rest->size] = '\0';
	ft_cpy_buffer_list_free(&(data->gnl),
		*line + data->line_size, (data->rd_size - rest->size) - 1);
	return (1);
}

int	ft_newline_in_buffer(struct s_data *data, struct s_mem *rest, char **line)
{
	data->ptrchr = ft_memchr(data->gnl->buf, '\n', data->rd_size);
	if (rest->status)
	{
		data->line_size = data->list_size + rest->size;
		*line = malloc(sizeof(char) * (data->line_size + 1));
		if (!*line)
		{
			data->error = E_MALLOC_FAIL;
			return (-1);
		}
		ft_memcpy(*line, rest->str, rest->size);
		(*line)[data->line_size] = '\0';
		ft_cpy_buffer_list_free(&(data->gnl),
			*line + data->line_size, data->line_size - rest->size);
		*rest = (struct s_mem){};
		return (1);
	}
	else if (data->ptrchr)
		return (ft_newline_bis(data, rest, line));
	return (0);
}

int	get_next_line_2(char **line, struct s_data *data, struct s_mem *rest)
{
	if (data->error)
	{
		ft_lstdelall(&(data->gnl));
		free(*line);
		*line = NULL;
		return (-1);
	}
	else if (!rest->size && !data->rd_size && !data->line_size)
	{
		ft_lstdelall(&(data->gnl));
		*line = NULL;
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line, int reset)
{
	static struct s_mem	rest = (struct s_mem){};
	struct s_data		data;

	data = (struct s_data){0};
	*line = NULL;
	if (reset)
	{
		rest = (struct s_mem){};
		ft_lstdelall(&(data.gnl));
		free(data.gnl);
	}
	if (rest.size && !ft_no_newline_in_rest(&data, &rest, line))
		return (data.line_size);
	else if (!rest.status)
	{
		while (!data.error && ft_lstaddnew_front(&data)
			&& ft_no_buffer_in_read(&data, &rest, fd)
			&& !ft_newline_in_buffer(&data, &rest, line))
			data.list_size += data.rd_size;
		return (get_next_line_2(line, &data, &rest));
	}
	return (0);
}
