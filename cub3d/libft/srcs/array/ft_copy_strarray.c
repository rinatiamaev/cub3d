/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:53:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 14:29:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_copy_strarray()
 * Creates a deep copy of a NULL-terminated array of strings.
 *
 * @array: The source array of strings to be copied.
 *
 * Returns:
 * - A newly allocated copy of the string array, or NULL on allocation failure.
 *
 * Usage:
 * - Use this function when you need an independent duplicate of a string array.
 * - The returned array must be freed with ft_free_array().
 */

char	**ft_copy_strarray(char **array)
{
	size_t	size;
	size_t	i;
	char	**copy;

	if (!array)
		return (NULL);
	size = ft_arraysize((void **)array);
	copy = malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			ft_free_array((void **)copy);
			return (NULL);
		}
		i++;
	}
	copy[size] = NULL;
	return (copy);
}
