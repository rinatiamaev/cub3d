/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_background_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:36:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:24:02 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Fills an image with ceiling and floor colors.
 *
 * This function writes pixel data directly to the given image buffer,
 * dividing the screen horizontally:
 * - The top half is filled with the `ceiling_color`.
 * - The bottom half is filled with the `floor_color`.
 *
 * Used to pre-render a static background image for the scene.
 *
 * @param img Pointer to the image structure to fill.
 * @param ceiling_color RGB color for the ceiling (top half).
 * @param floor_color RGB color for the floor (bottom half).
 */
static inline void	fill_background(t_img *img, int ceiling_color,
															int floor_color)
{
	int	y;
	int	x;
	int	*row;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		row = (int *)(img->addr + y * img->line_size);
		while (x < WIN_W)
		{
			if (y < WIN_H >> 1)
				row[x] = ceiling_color;
			else
				row[x] = floor_color;
			x++;
		}
		y++;
	}
}

/**
 * @brief Initializes and prepares the static background image.
 *
 * This function creates a new image the size of the window and fills it
 * using the configured ceiling and floor colors from the map settings.
 *
 * The image is stored in `game->bg_img` and reused during rendering
 * to avoid redrawing the background every frame.
 *
 * @param game Pointer to the game state (map config and image context).
 */
void	init_background(t_game *game)
{
	game->bg_img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->bg_img.addr = mlx_get_data_addr(game->bg_img.ptr, &game->bg_img.bpp,
			&game->bg_img.line_size, &game->bg_img.endian);
	fill_background(&game->bg_img, game->map->conf.ceiling_color,
		game->map->conf.floor_color);
}
