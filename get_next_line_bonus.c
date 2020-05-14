/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmon <charmon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:32:23 by charmon           #+#    #+#             */
/*   Updated: 2020/05/14 23:15:55 by charmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	del_descroptor(t_descriptor *for_del, t_descriptor **d)
{
	t_descriptor		*tmp;
	int					i;

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
	char	buf[BUFFER_SIZE + 1];
	size_t	ret;
	char	*new_line;

	if (!(ret = read(descriptor->fd, buf, BUFFER_SIZE)))
		return (0);
	buf[BUFFER_SIZE] = '\0';
	if (!descriptor->data)
		descriptor->data = ft_strdup(buf);
	else
	{
		new_line = ft_strjoin(descriptor->data, buf);
		free(descriptor->data);
		descriptor->data = new_line;
	}
	return (ret);
}

char	*get_line(t_descriptor *d)
{
	size_t	len;
	size_t	idx;
	char	*line;
	char	*remainder;
	char	*n;

	n = ft_strchr(d->data, '\n');
	len = (n) ? n - d->data : ft_strlen(d->data);
	line = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(line, d->data, len + 1);
	if (d->data[0] == '\n')
		len++;
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(d->data) - len + 1));
	idx = 0;
	while (d->data[len] != '\0')
		remainder[idx++] = d->data[len++];
	if (idx)
	{
		remainder[idx] = '\0';
		free(d->data);
		d->data = remainder;
	}
	else
	{
		free(remainder);
		free(d->data);
		d->data = NULL;
	}
	return (line);
}

int		processing(t_descriptor *current, t_descriptor **d, char **line)
{
	size_t	append_count;

	append_count = 1;
	while ((!current->data || !ft_strchr(current->data, '\n')) && append_count)
		append_count = append_data(current);
	if (!current->data)
	{
		del_descroptor(current, d);
		return (-1);
	}
	*line = get_line(current);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_descriptor	*d;
	t_descriptor		*current;

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
