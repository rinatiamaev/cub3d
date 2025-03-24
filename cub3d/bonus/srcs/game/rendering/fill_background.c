/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:36:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:38:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	init_background(t_game *game)
{
	game->bg_img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->bg_img.addr = mlx_get_data_addr(game->bg_img.ptr, &game->bg_img.bpp,
			&game->bg_img.line_size, &game->bg_img.endian);
	fill_background(&game->bg_img, game->map->conf.ceiling_color,
		game->map->conf.floor_color);
}
