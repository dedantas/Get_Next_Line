/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:18:09 by dedantas          #+#    #+#             */
/*   Updated: 2025/05/22 14:13:48 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_have_newline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static int	read_into_buffer(int fd, char **buf)
{
	char	*temp;
	int		bytes;

	bytes = 1;
	while (!ft_have_newline(*buf) && bytes > 0)
	{
		temp = malloc(BUFFER_SIZE + 1);
		if (!temp)
			return (-1);
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(temp);
			return (bytes);
		}
		temp[bytes] = '\0';
		*buf = ft_strjoin(*buf, temp);
		free(temp);
		if (!*buf)
			return (-1);
	}
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	bytes = read_into_buffer(fd, &buf);
	if (bytes < 0)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	line = ft_extract_line(&buf);
	if (!line || !*line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	return (line);
}

#include <stdio.h>
int	main()
{
	char	*line;
	int	fd;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("LINE: %s", line);
		free(line);
	}
	close(fd);
}
