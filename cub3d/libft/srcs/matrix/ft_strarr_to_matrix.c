/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_to_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:00:51 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 15:36:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_strarr_to_matrix()
 * Converts a NULL-terminated string array into a 2D integer matrix.
 *
 * @array: The NULL-terminated array of strings.
 *
 * Returns: A dynamically allocated integer matrix or NULL on failure.
 */
int	**ft_strarr_to_matrix(char **array)
{
	size_t	rows;
	size_t	cols;
	int		**matrix;
	size_t	i;
	size_t	j;

	rows = ft_arraysize((void **)array);
	cols = ft_strlen(array[0]);
	matrix = ft_create_matrix(rows, cols);
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			matrix[i][j] = array[i][j] - '0';
			j++;
		}
		i++;
	}
	return (matrix);
}
