/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmon <charmon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:32:23 by charmon           #+#    #+#             */
/*   Updated: 2020/05/17 23:28:47 by charmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	del_descroptor(t_descriptor *for_del, t_descriptor **d)
{
	t_descriptor	*tmp;
	int				i;

	i = 0;
	if (d[0] && d[0]->fd == for_del->fd)
	{
		tmp = *d;
		*d = (*d)->next;
		if (tmp->data != NULL)
			free(tmp->data);
		free(tmp);
		return ;
	}
	while (d[i] != NULL && d[i]->fd != for_del->fd)
	{
		tmp = d[i];
		i++;
	}
	if (d[i])
	{
		*d = (*d)->next;
		if (tmp->data != NULL)
			free(tmp->data);
		free(tmp);
	}
}

int		append_data(t_descriptor *descriptor)
{
	char	*buf;
	int		ret;
	char	*new_line;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ret = read(descriptor->fd, buf, BUFFER_SIZE);
	if (!(ret == 0 || ret == -1))
	{
		buf[ret] = '\0';
		if (!descriptor->data)
		{
			if (!(descriptor->data = ft_strdup(buf)))
				ret = -1;
		}
		else
		{
			if (!(new_line = ft_strjoin(descriptor->data, buf)))
				ret = -1;
			free(descriptor->data);
			descriptor->data = new_line;
		}
	}
	free(buf);
	return (ret);
}

int		get_line(t_descriptor *d, char **line)
{
	size_t	len;
	size_t	idx;
	int		result;
	char	*remainder;
	char	*n;

	n = ft_strchr(d->data, '\n');
	len = (n) ? (size_t)(n - d->data) : ft_strlen(d->data);
	result = (n) ? 1 : 0;
	if (!(*line = (char *)malloc(sizeof(char) * (len + 1))))
		return (-1);
	ft_strlcpy(*line, d->data, len + 1);
	if (result)
		len++;
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(d->data) - len + 1));
	if (!remainder)
		return (-1);
	idx = 0;
	while (d->data[len] != '\0')
		remainder[idx++] = d->data[len++];
	remainder[idx] = '\0';
	free(d->data);
	d->data = remainder;
	return (result);
}

int		processing(t_descriptor *current, t_descriptor **d, char **line)
{
	int		append_count;
	int		get_line_result;

	append_count = 1;
	while ((!current->data || !ft_strchr(current->data, '\n'))
							&& append_count >= 1)
		append_count = append_data(current);
	if (!current->data || append_count == -1)
	{
		del_descroptor(current, d);
		if (!(*line = ft_strdup("\0")))
			return (-1);
		return (append_count);
	}
	get_line_result = get_line(current, line);
	if (get_line_result <= 0)
		del_descroptor(current, d);
	return (get_line_result);
}

int		get_next_line(int fd, char **line)
{
	static t_descriptor	*d;
	t_descriptor		*current;

	if (fd < 0 || line == NULL)
		return (-1);
	current = d;
	while (current != NULL)
	{
		if (current->fd == fd)
			break ;
		current = current->next;
	}
	if (!current)
	{
		if (!(current = (t_descriptor *)malloc(sizeof(t_descriptor))))
			return (-1);
		current->fd = fd;
		current->data = NULL;
		current->next = d;
		d = current;
	}
	return (processing(current, &d, line));
}
