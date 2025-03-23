/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:47:15 by riamaev           #+#    #+#             */
/*   Updated: 2025/03/23 20:43:24 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Draw a single square block on minimap
static void	draw_square_block(t_game *game, t_point pos, int size, int color)
{
	t_point	offset;

	offset.y = 0;
	while (offset.y < size)
	{
		offset.x = 0;
		while (offset.x < size)
		{
			put_pixel(&game->img, pos.x + offset.x,
				pos.y + offset.y, color);
			offset.x++;
		}
		offset.y++;
	}
}

// Draw all walls on minimap
static void	draw_minimap_walls(t_game *game, int tile_size)
{
	t_point	map_pos;
	t_point	minimap_pos;

	map_pos.y = 0;
	while (map_pos.y < game->map->size.y)
	{
		map_pos.x = 0;
		while (map_pos.x < game->map->size.x)
		{
			if (game->map->matrix[map_pos.y][map_pos.x] == 1)
			{
				minimap_pos = get_minimap_position(map_pos, tile_size);
				draw_square_block(game, minimap_pos, tile_size, WALL_COLOR);
			}
			map_pos.x++;
		}
		map_pos.y++;
	}
}

// Draw the player's token on minimap
static void	draw_player_on_minimap(t_game *game, int tile_size, int player_radius)
{
	t_point	player_center;
	t_point	offset;
	t_point	draw_pos;

	player_center.x = MINIMAP_OFFSET_X + game->player.pos.x * tile_size;
	player_center.y = MINIMAP_OFFSET_Y + game->player.pos.y * tile_size;
	offset.y = -player_radius;
	while (offset.y <= player_radius)
	{
		offset.x = -player_radius;
		while (offset.x <= player_radius)
		{
			if (is_point_in_circle(offset, player_radius))
			{
				draw_pos.x = player_center.x + offset.x;
				draw_pos.y = player_center.y + offset.y;
				put_pixel(&game->img, draw_pos.x, draw_pos.y, PLAYER_COLOR);
			}
			offset.x++;
		}
		offset.y++;
	}
}

// Main minimap drawing function
void	draw_minimap(t_game *game)
{
	int	tile_size;
	int	player_radius;

	if (!game->minimap_visible)
		return ;
	tile_size = get_tile_size(game->map);
	player_radius = tile_size * PLAYER_SCALE;
	draw_minimap_walls(game, tile_size);
	draw_player_on_minimap(game, tile_size, player_radius);
}

