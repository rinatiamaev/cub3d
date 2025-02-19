/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:18:47 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 15:28:32 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_free_matirx()
 * Frees a 2D integer matrix.
 *
 * @matrix: The matrix to free.
 * @rows: The number of rows.
 */
void	ft_free_matrix(int **matrix, size_t rows)
{
	size_t	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < rows)
		free(matrix[i++]);
	free(matrix);
}
