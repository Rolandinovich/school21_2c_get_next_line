/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmon <charmon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:29:07 by charmon           #+#    #+#             */
/*   Updated: 2020/05/12 23:59:50 by charmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define BUFFER_SIZE 32
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct			s_descriptor
{
	int					fd;
	char				*data;
	struct s_descriptor	*next;
}						t_descriptor;

int 					get_next_line(int fd, char **line);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);

#endif
