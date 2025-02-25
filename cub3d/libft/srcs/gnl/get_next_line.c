/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:53:52 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/25 13:53:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * read_and_store()
 * Reads from a file descriptor and stores the content in a buffer.
 * It dynamically expands the remainder until a newline is found or EOF.
 *
 * @fd: The file descriptor to read from.
 * @remainder: A pointer to the remainder string, storing unprocessed content.
 *
 * Returns: The number of bytes read, or -1 on failure.
 *
 * - Uses a buffer of size BUFFER_SIZE for reading.
 * - Concatenates new data to the remainder and checks for newline.
 * - If a read error occurs, frees allocated memory and returns -1.
 */
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

/**
 * extract_line()
 * Extracts a single line (ending with '\n' if present) from the remainder.
 *
 * @remainder: The remainder string containing buffered content.
 *
 * Returns: A newly allocated string containing the next line,
 * or NULL if no valid line is found.
 *
 * - The function scans for the first newline character (`\n`).
 * - If found, it includes the newline in the extracted line.
 * - If the remainder is empty, returns NULL.
 */
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

/**
 * update_remainder()
 * Updates the remainder by removing the extracted line,
 * keeping only the unprocessed content.
 *
 * @remainder: The current remainder string.
 *
 * Returns: A newly allocated string with the remaining content,
 * or NULL if there is no leftover data.
 *
 * - Frees the previous remainder and returns a new trimmed version.
 * - If no extra content remains after extracting the line, returns NULL.
 */
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

/**
 * get_next_line()
 * Reads the next line from a file descriptor.
 *
 * @fd: The file descriptor to read from.
 *
 * Returns: A dynamically allocated string containing the next line,
 * or NULL if there is nothing left to read or an error occurs.
 *
 * Usage:
 * - Use `get_next_line()` in a loop to read a file line by line.
 * - The function manages a static buffer (`remainder`) per file descriptor.
 * - Supports multiple file descriptors simultaneously.
 * - The caller is responsible for freeing the returned line.
 */
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
