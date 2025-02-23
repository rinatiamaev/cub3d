/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riamaev <riamaev@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:47:15 by riamaev           #+#    #+#             */
/*   Updated: 2025/02/23 15:47:17 by riamaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	fill_minimap_background(t_game *game, t_minimap *minimap)
{
	int	x;
	int	y;

	(void)minimap;
	y = MINIMAP_OFFSET_Y;
	while (y < MINIMAP_OFFSET_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_OFFSET_X;
		while (x < MINIMAP_OFFSET_X + MINIMAP_SIZE)
		{
			put_pixel(&game->img, x, y, BACKGROUND_COLOR | TRANSPARENCY);
			x++;
		}
		y++;
	}
}

static void	draw_wall_block(t_game *game, int draw_x, int draw_y, \
			t_minimap *minimap)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < minimap->wall_size)
	{
		dx = 0;
		while (dx < minimap->wall_size)
		{
			put_pixel(&game->img, draw_x + dx, draw_y + dy, WALL_COLOR);
			dx++;
		}
		dy++;
	}
}

static void	draw_walls(t_game *game, t_minimap *minimap)
{
	int	map_x;
	int	map_y;
	int	draw_x;
	int	draw_y;

	map_y = 0;
	while (map_y < game->map->size.y)
	{
		map_x = 0;
		while (map_x < game->map->size.x)
		{
			draw_x = MINIMAP_OFFSET_X + map_x * minimap->tile_w \
			+ minimap->wall_offset;
			draw_y = MINIMAP_OFFSET_Y + map_y * minimap->tile_h \
			+ minimap->wall_offset;
			if (game->map->matrix[map_y][map_x] == 1)
				draw_wall_block(game, draw_x, draw_y, minimap);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player(t_game *game, t_minimap *minimap)
{
	int	dx;
	int	dy;
	int	player_x;
	int	player_y;

	dy = -minimap->player_radius;
	player_x = MINIMAP_OFFSET_X + game->player.pos.x * minimap->tile_w;
	player_y = MINIMAP_OFFSET_Y + game->player.pos.y * minimap->tile_h;
	while (dy <= minimap->player_radius)
	{
		dx = -minimap->player_radius;
		while (dx <= minimap->player_radius)
		{
			if (dx * dx + dy * dy <= minimap->player_radius \
			* minimap->player_radius)
			{
				put_pixel(&game->img, player_x + dx, player_y \
				+ dy, PLAYER_COLOR);
			}
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	minimap;

	minimap.tile_w = MINIMAP_SIZE / game->map->size.x;
	minimap.tile_h = MINIMAP_SIZE / game->map->size.y;
	minimap.wall_size = minimap.tile_w * WALL_SCALE;
	minimap.wall_offset = (minimap.tile_w - minimap.wall_size) / 2;
	minimap.player_radius = minimap.tile_w * PLAYER_SCALE;
	fill_minimap_background(game, &minimap);
	draw_walls(game, &minimap);
	draw_player(game, &minimap);
}
