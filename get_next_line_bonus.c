/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmon <charmon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:32:23 by charmon           #+#    #+#             */
/*   Updated: 2020/05/12 23:59:50 by charmon          ###   ########.fr       */
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

int		get_line(t_descriptor *current, t_descriptor **d, char **line)
{
	int 	r_count;
	char 	buf[BUFFER_SIZE + 1];

	if (!current->data || !ft_strchr(current->data, '\n'))
	{
		if (!(r_count = read(current->fd, buf, BUFFER_SIZE)))
		{
			del_descroptor(current, d);
			return (-1);
		}
		buf[BUFFER_SIZE] = '\0';
		current->data = ft_strjoin(current->data, buf);
	}
	if (r_count < BUFFER_SIZE)
	{

	}

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
	return (get_line(current, &d, line));
}
