/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmon <charmon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:29:07 by charmon           #+#    #+#             */
/*   Updated: 2020/05/15 22:39:36 by charmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int			main(void)
{
	char	*line;
	int		fd;
	int		res;

	fd = open("/home/roman/CLionProjects/local_projects_scholl_21/school21_2c_get_next_line/5line", O_RDONLY);
//	fd = open("/home/roman/CLionProjects/local_projects_scholl_21/school21_2c_get_next_line/max", O_RDONLY);
	res = 1;
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		if (res)
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	return (0);
}
