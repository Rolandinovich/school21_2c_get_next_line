/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmon <charmon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:38:09 by charmon           #+#    #+#             */
/*   Updated: 2020/05/12 23:54:45 by charmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*ft_strchr(const char *s, int c)
{
	size_t	idx;

	idx = 0;
	while (s[idx] != '\0' && s[idx] != c)
		idx++;
	if (s[idx] == '\0' && c != '\0')
		return (NULL);
	else
		return ((char *)(&s[idx]));
}

size_t		ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;

	if (!dst && !src)
		return (0);
	if (!dst && src)
		return (ft_strlen(src));
	count = 0;
	while (src[count] != '\0' && count < size - 1 && size != 0)
	{
		dst[count] = src[count];
		count++;
	}
	if (size != 0)
		dst[count] = '\0';
	while (src[count] != '\0')
		count++;
	return (count);
}

char		*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_line;

	len = ft_strlen(s);
	new_line = (char *)malloc((len + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, s, len + 1);
	return (new_line);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	idx;
	size_t	idx2;
	size_t	len;
	char	*rst;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	rst = (char *)malloc((len + 1) * sizeof(char));
	if (!rst)
		return (NULL);
	idx = -1;
	while (s1[++idx] != '\0')
		rst[idx] = s1[idx];
	idx2 = idx;
	idx = -1;
	while (s2[++idx] != '\0')
		rst[idx2++] = s2[idx];
	rst[idx2] = '\0';
	return (rst);
}