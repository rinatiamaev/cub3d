/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:47:15 by riamaev           #+#    #+#             */
/*   Updated: 2025/02/26 21:24:17 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_wall_block(t_game *game, t_point minimap_pos, int tile_size)
{
	t_point	offset;

	offset.y = 0;
	while (offset.y < tile_size)
	{
		offset.x = 0;
		while (offset.x < tile_size)
		{
			put_pixel(&game->img, minimap_pos.x + offset.x,
				minimap_pos.y + offset.y, WALL_COLOR);
			offset.x++;
		}
		offset.y++;
	}
}

static void	draw_walls(t_game *game, int tile_size)
{
	t_point	map_pos;
	t_point	minimap_pos;

	map_pos.y = 0;
	while (map_pos.y < game->map->size.y)
	{
		map_pos.x = 0;
		while (map_pos.x < game->map->size.x)
		{
			minimap_pos.x = MINIMAP_OFFSET_X + map_pos.x * tile_size;
			minimap_pos.y = MINIMAP_OFFSET_Y + map_pos.y * tile_size;
			if (game->map->matrix[map_pos.y][map_pos.x] == 1)
				draw_wall_block(game, minimap_pos, tile_size);
			map_pos.x++;
		}
		map_pos.y++;
	}
}

static void	draw_player(t_game *game, int tile_size, int player_radius)
{
	t_point	player_pos;
	t_point	player_offset;

	player_offset.y = -player_radius;
	player_pos.x = MINIMAP_OFFSET_X + game->player.pos.x * tile_size;
	player_pos.y = MINIMAP_OFFSET_Y + game->player.pos.y * tile_size;
	while (player_offset.y <= player_radius)
	{
		player_offset.x = -player_radius;
		while (player_offset.x <= player_radius)
		{
			if (player_offset.x * player_offset.x
				+ player_offset.y * player_offset.y
				<= player_radius * player_radius)
			{
				put_pixel(&game->img, player_pos.x + player_offset.x,
					player_pos.y + player_offset.y, PLAYER_COLOR);
			}
			player_offset.x++;
		}
		player_offset.y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	tile_size;
	int	player_radius;

	if (!game->minimap_visible)
		return ;
	tile_size = fmin(MINIMAP_SIZE / game->map->size.x,
			MINIMAP_SIZE / game->map->size.y);
	player_radius = tile_size * PLAYER_SCALE;
	draw_walls(game, tile_size);
	draw_player(game, tile_size, player_radius);
}
