/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_memory_utils_two_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:57:43 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:03:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Creates a deep copy of a NULL-terminated string array.
 *
 * Wraps ft_copy_strarray and triggers an error if allocation fails.
 *
 * @param game Pointer to the game context (used in case of error).
 * @param array NULL-terminated array of strings to copy.
 * @return Newly allocated deep copy of the string array.
 */
char	**x_copy_strarray(t_game *game, char **array)
{
	char	**copy;

	copy = ft_copy_strarray(array);
	if (!copy)
		error(game, "ft_copy_strarray() failed");
	return (copy);
}

/**
 * @brief Allocates a 2D matrix of integers with given dimensions.
 *
 * Wraps ft_create_matrix and handles memory errors by exiting.
 *
 * @param game Pointer to the game context (used in case of error).
 * @param row_count Number of rows to allocate.
 * @param col_count Number of columns to allocate.
 * @return Pointer to the allocated 2D integer matrix.
 */
int	**x_create_matrix(t_game *game, int row_count, int col_count)
{
	int	**matrix;

	matrix = ft_create_matrix(row_count, col_count);
	if (!matrix)
		error(game, "ft_create_matrix() failed");
	return (matrix);
}

/**
 * @brief Converts an integer to a string with error handling.
 *
 * Wraps ft_itoa and terminates on failure.
 *
 * @param game Pointer to the game context (used in case of error).
 * @param n Integer to convert.
 * @return Newly allocated string representation of the integer.
 */
char	*x_itoa(t_game *game, int n)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
		error(game, "ft_itoa() failed");
	return (str);
}
