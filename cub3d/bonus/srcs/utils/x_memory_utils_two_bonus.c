/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_memory_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:57:43 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 19:52:39 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**x_copy_strarray(t_game *game, char **array)
{
	char	**copy;

	copy = ft_copy_strarray(array);
	if (!copy)
		error(game, "ft_copy_strarray() failed");
	return (copy);
}

int	**x_create_matrix(t_game *game, int row_count, int col_count)
{
	int	**matrix;

	matrix = ft_create_matrix(row_count, col_count);
	if (!matrix)
		error(game, "ft_create_matrix() failed");
	return (matrix);
}

char	*x_itoa(t_game *game, int n)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
		error(game, "ft_itoa() failed");
	return (str);
}
