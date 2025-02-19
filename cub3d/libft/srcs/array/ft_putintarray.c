/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putintarray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:17:44 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 15:10:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_putintarray()
 * Prints an array of int separated by spaces.
 *
 * @array: The array of integers to be printed.
 * @size: The number of elements in the array.
 *
 * Returns: The total number of bytes written, or -1 if an error occurs.
 *
 * Usage:
 * - Use this function to display an integer array in a space-separated format.
 * - Returns the bytes written for potential error handling.
 *
 * Notes:
 * - If `array` is NULL or `size` is 0, the function does nothing and returns 0.
 * - The function does not print a newline; add "\n" manually if needed.
 */
int	ft_putintarray(int *array, int size)
{
	int	total_bytes;
	int	bytes_written;
	int	i;

	if (!array || size <= 0)
		return (0);
	total_bytes = 0;
	i = 0;
	while (i < size)
	{
		bytes_written = ft_printf("%d", array[i]);
		if (bytes_written < 0)
			return (-1);
		total_bytes += bytes_written;
		if (i < size - 1)
		{
			bytes_written = ft_printf(" ");
			if (bytes_written < 0)
				return (-1);
			total_bytes += bytes_written;
		}
		i++;
	}
	return (total_bytes);
}
