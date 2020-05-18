/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmon <charmon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:29:07 by charmon           #+#    #+#             */
/*   Updated: 2020/05/17 22:04:21 by charmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


int			main(void)
{
	char	*line;
	int		fd;
	int		res;
	int 	fd_list[10000];
	int 	idx;
	int 	iter_count;
	char 	for_next[10];


	printf("Тест стандартного инпута\n\n");
	res = 1;
	while (res == 1)
	{
		res = get_next_line(1, &line);
		if (res)
			printf("%s\n", line);
		free(line);
		line = NULL;
	}

	printf("Базовые тесты\n\n");
	fd = open("/home/roman/CLionProjects/local_projects_scholl_21/school21_2c_get_next_line/basic_tests", O_RDONLY);
//	fd = open("basic_tests", O_RDONLY);
	res = 1;
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		printf("%s\n", line);
		free(line);
		line = NULL;
	}

	res = 1;
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		if (res == 0)
			printf("%s\n", line);
		free(line);
		line = NULL;
	}
	res = 1;

	while (res == 1)
	{
		res = get_next_line(42, &line);
		if (res > 0)
			printf("%s\n", line);
		free(line);
		line = NULL;
	}

	fd = open("/home/roman/CLionProjects/local_projects_scholl_21/school21_2c_get_next_line/null_line", O_RDONLY);
//	fd = open("null_line", O_RDONLY);
	res = 1;
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		if (res == 0)
			printf("Должно быть пусто : \"%s\" \n", line);
		free(line);
		line = NULL;
	}

	for (iter_count = 0; iter_count < 4; iter_count++)
	{
		idx = -1;
		while (++idx < 4)
		{
			if (!iter_count)
				fd_list[idx] = open("/home/roman/CLionProjects/local_projects_scholl_21/school21_2c_get_next_line/basic_tests", O_RDONLY);
//				fd_list[idx] = open("basic_tests", O_RDONLY);
			printf("fd :%d\n",fd_list[idx]);
			res = 1;
			res = get_next_line(fd_list[idx], &line);
			if (res == 1)
				printf("%s\n", line);
			free(line);
			line = NULL;
		}
	}
	printf("Количество прочитанных файлов : %d\n\n", idx);

	printf("Длинный текст \n\n");
	scanf("%s:\n", for_next);
	fd = open("/home/roman/CLionProjects/local_projects_scholl_21/school21_2c_get_next_line/max", O_RDONLY);
//	fd = open("max", O_RDONLY);
	res = 1;
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		printf("%s\n", line);
		free(line);
		line = NULL;
	}

	return (0);
}
