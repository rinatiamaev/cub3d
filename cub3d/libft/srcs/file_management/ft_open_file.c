/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:28:38 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/18 23:34:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * ft_open_file - Opens a file safely and checks for errors.
 *
 * @filename: The path to the file.
 * @flags: The open() flags (e.g., O_RDONLY, O_WRONLY).
 *
 * Returns:
 * - A valid file descriptor (>= 0) on success.
 * - -1 if the file could not be opened (error message is printed).
 */
int	ft_open_file(const char *filename, int flags)
{
	int	fd;

	if (!filename)
	{
		write(2, "Error: Invalid filename\n", 24);
		return (-1);
	}
	fd = open(filename, flags);
	if (fd < 0)
		perror("Error opening file");
	return (fd);
}
