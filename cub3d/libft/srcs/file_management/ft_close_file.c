/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:36:14 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/18 23:41:44 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_safe_close - Safely closes a file descriptor and returns status.
 *
 * @fd: The file descriptor to close.
 *
 * Returns:
 * - 0 on success.
 * - -1 on error (prints an error message).
 */
int	ft_safe_close(int fd)
{
	if (fd >= 0)
	{
		if (close(fd) < 0)
		{
			perror("Error closing file");
			return (-1);
		}
	}
	return (0);
}
