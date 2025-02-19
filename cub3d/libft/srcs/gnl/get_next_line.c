/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:40:32 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/18 23:58:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	read_and_store(int fd, char **remainder)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*new_remainder;

	if (*remainder == NULL)
		*remainder = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = 1;
	while ((ft_strchr(*remainder, '\n') == NULL) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), -1);
		buffer[bytes_read] = '\0';
		new_remainder = ft_strjoin(*remainder, buffer);
		if (!new_remainder)
			return (free(buffer), -1);
		free(*remainder);
		*remainder = new_remainder;
	}
	free(buffer);
	return (bytes_read);
}

static char	*extract_line(char *remainder)
{
	size_t	line_len;
	char	*line;

	line_len = 0;
	if (!remainder || !remainder[0])
		return (NULL);
	while (remainder[line_len] && remainder[line_len] != '\n')
		line_len++;
	if (remainder[line_len] == '\n')
		line_len++;
	line = ft_substr(remainder, 0, line_len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	size_t	line_len;
	size_t	remainder_len;

	if (!remainder)
		return (NULL);
	line_len = 0;
	while (remainder[line_len] && remainder[line_len] != '\n')
		line_len++;
	if (remainder[line_len] == '\n')
		line_len++;
	if (remainder[line_len] == '\0')
	{
		free(remainder);
		return (NULL);
	}
	remainder_len = ft_strlen(remainder);
	new_remainder = ft_substr(remainder, line_len, remainder_len - line_len);
	free(remainder);
	if (!new_remainder)
		return (NULL);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	if (!remainder[fd])
	{
		remainder[fd] = ft_strdup("");
		if (!remainder[fd])
			return (NULL);
	}
	bytes_read = read_and_store(fd, &remainder[fd]);
	if (bytes_read == -1 || (bytes_read == 0 && remainder[fd][0] == '\0'))
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	line = extract_line(remainder[fd]);
	if (!line)
		return (NULL);
	remainder[fd] = update_remainder(remainder[fd]);
	return (line);
}
