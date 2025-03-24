/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:33:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:43:31 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_create_matrix()
 * Allocates a 2D integer matrix with the given dimensions.
 *
 * @rows: Number of rows in the matrix.
 * @cols: Number of columns in each row.
 *
 * Returns:
 * - A pointer to the allocated matrix (an array of integer pointers).
 * - NULL if memory allocation fails.
 *
 * Description:
 * - This function dynamically allocates memory for a 2D integer matrix.
 * - Each row is allocated separately using `ft_calloc()`, ensuring that all
 *   elements are initialized to 0.
 * - If any allocation fails, the function safely frees already allocated rows
 *   using `ft_free_matrix()` and returns NULL to prevent memory leaks.
 */

int	**ft_create_matrix(size_t rows, size_t cols)
{
	int		**matrix;
	size_t	i;

	matrix = (int **)ft_calloc(rows, sizeof(int *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		matrix[i] = (int *)ft_calloc(cols, sizeof(int));
		if (!matrix[i])
		{
			ft_free_matrix(matrix, i);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}
