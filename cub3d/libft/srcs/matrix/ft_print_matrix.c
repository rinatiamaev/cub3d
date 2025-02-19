/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:59:23 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 15:07:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_matrix_print()
 * Prints a 2D integer matrix with error handling.
 *
 * @matrix: The matrix to print.
 * @rows: The number of rows.
 * @cols: The number of columns.
 *
 * If an error occurs during writing, it returns (-1).
 */
int	ft_print_matrix(int **matrix, size_t rows, size_t cols)
{
	size_t	i;
	size_t	j;
	int		bytes_written;

	if (!matrix)
		return (-1);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			bytes_written = ft_printf("%d ", matrix[i][j]);
			if (bytes_written < 0)
				return (-1);
			j++;
		}
		bytes_written = ft_printf("\n");
		if (bytes_written < 0)
			return (-1);
		i++;
	}
	return (0);
}
