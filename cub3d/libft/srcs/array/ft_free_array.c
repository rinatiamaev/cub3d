/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:58:55 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 01:27:24 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_free_array()
 * Frees a NULL-terminated array of dynamically allocated elements.
 *
 * @array: A pointer to a NULL-terminated array of pointers.
 *
 * Usage:
 * - Use this function to free arrays of dynamically allocated strings or other
 *  heap-allocated elements.
 * - The array itself is also freed, so do not use the pointer after calling
 * this function.
 * - If `array` is NULL, the function does nothing.
 */

void	ft_free_array(void **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	ft_free_array_size(void **array, size_t size)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}
