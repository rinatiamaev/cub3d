/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraysize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:39:51 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 15:11:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_arraysize()
 * Calculates the number of elements in a NULL-terminated array.
 *
 * @array: The NULL-terminated array (can be of any type).
 *
 * Returns: The number of elements (excluding the NULL terminator).
 *
 * Usage:
 * - Works for any NULL-terminated array (e.g., `char **`, `int **`, `void **`).
 * - If `array` is NULL, the function returns 0.
 */
size_t	ft_arraysize(void **array)
{
	size_t	size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	return (size);
}
