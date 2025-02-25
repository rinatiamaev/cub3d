/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:12:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/25 22:18:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	error(t_game *game, char *err_msg)
{
	if (game)
		free_game(game);
	if (err_msg)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putendl_fd(err_msg, STDERR_FILENO);
	}
	if (errno)
		perror("");
	exit(EXIT_FAILURE);
}

int	**x_create_matrix(t_game *game, int row_count, int col_count)
{
	int	**matrix;

	matrix = ft_create_matrix(row_count, col_count);
	if (!matrix)
		error(game, "ft_create_matrix() failed");
	return (matrix);
}
