/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:34:38 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/18 23:35:17 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_read_file - Reads data from a file descriptor safely.
 *
 * @fd: The file descriptor.
 * @buffer: The buffer to store data.
 * @size: The number of bytes to read.
 *
 * Returns:
 * - The number of bytes read on success.
 * - -1 on error (error message printed).
 */
ssize_t	ft_read_file(int fd, void *buffer, size_t size)
{
	ssize_t	bytes_read;

	if (fd < 0 || !buffer)
	{
		write(2, "Error: Invalid file descriptor or buffer\n", 41);
		return (-1);
	}
	bytes_read = read(fd, buffer, size);
	if (bytes_read < 0)
		perror("Error reading file");
	return (bytes_read);
}
