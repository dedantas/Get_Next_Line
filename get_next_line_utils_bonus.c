/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:42:32 by dedantas          #+#    #+#             */
/*   Updated: 2025/05/22 15:42:56 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdub(char *s1)
{
	char			*dest;
	unsigned int	i;

	dest = malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*res;
	size_t		i;
	size_t		j;
	size_t		total_len;

	if (!s1 && !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(total_len + 1);
	if (!res)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (free(s1), res);
}

char	*ft_extract_line_from_buffer(char **buffer, size_t *line_len)
{
	char	*line;
	size_t	i;

	if (!buffer || !*buffer || !**buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	*line_len = i;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_extract_line(char **buffer)
{
	char	*line;
	char	*new_buf;
	size_t	line_len;
	size_t	i;

	if (!buffer || !*buffer || !**buffer)
		return (NULL);
	line = ft_extract_line_from_buffer(buffer, &line_len);
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = (*buffer)[i];
		i++;
	}
	line[i] = '\0';
	new_buf = ft_strdub(*buffer + line_len);
	free(*buffer);
	*buffer = new_buf;
	return (line);
}
