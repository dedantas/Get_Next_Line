/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:44:34 by dedantas          #+#    #+#             */
/*   Updated: 2025/05/22 15:59:51 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buf[1024];
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	bytes = read_into_buffer(fd, &buf[fd]);
	if (bytes < 0)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	line = ft_extract_line(&buf[fd]);
	if (!line || !*line)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	return (line);
}

/*#include <stdio.h>
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
}*/
