/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:47:15 by riamaev           #+#    #+#             */
/*   Updated: 2025/04/02 21:19:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Draws a filled square block on the screen at a given position.
 *
 * This function renders a solid square of a specified `size` and `color`
 * directly into the image buffer. It uses pixel-level access to draw the
 * square starting from the top-left corner `pos`.
 *
 * Commonly used for drawing walls or other map elements on the minimap.
 *
 * @param game Pointer to the game state (provides access to the image buffer).
 * @param pos Top-left corner of the square in screen-space.
 * @param size Width and height of the square in pixels.
 * @param color RGB color value to fill the square with.
 */
static void	draw_square_block(t_game *game, t_point pos, int size, int color)
{
	int		y;
	int		x;
	char	*row_start;
	char	*dst;

	y = 0;
	while (y < size)
	{
		row_start = game->img.addr + ((pos.y + y) * game->img.line_size)
			+ (pos.x * (game->img.bpp >> 3));
		x = 0;
		dst = row_start;
		while (x < size)
		{
			*(unsigned int *)dst = color;
			dst += (game->img.bpp >> 3);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draws all wall tiles on the minimap.
 *
 * This function iterates over the 2D map matrix and checks each cell.
 * If the value at a position indicates a wall (value == 1), it calculates
 * the corresponding screen position using `get_minimap_position` and draws
 * a solid square using `draw_square_block`.
 *
 * This provides a top-down view of the static map layout for the minimap.
 *
 * @param game Pointer to the game state (provides access to map and buffer).
 * @param tile_size The size of each tile on the minimap in pixels.
 */
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

/**
 * @brief Draws the player icon on the minimap as a filled circle.
 *
 * This function calculates the screen-space position of the player on
 * the minimap using their world position and the current tile size.
 * It then iterates over a square area around that center point and uses
 * `is_point_in_circle` to draw only the pixels within a circular area.
 *
 * The result is a circular dot representing the player, rendered in
 * `PLAYER_COLOR`.
 *
 * @param game Pointer to the game state (provides player data and image buffer).
 * @param tile_size The pixel size of a single map tile.
 * @param player_radius The radius in pixels of the circular player icon.
 */
static void	draw_player_on_minimap(t_game *game, int tile_size,
														int player_radius)
{
	t_point	player_center;
	t_point	offset;
	t_point	draw_pos;
	char	*dst;

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
				dst = game->img.addr + (draw_pos.y * game->img.line_size)
					+ (draw_pos.x * (game->img.bpp >> 3));
				*(unsigned int *)dst = PLAYER_COLOR;
			}
			offset.x++;
		}
		offset.y++;
	}
}

/**
 * @brief Renders the minimap including walls and the player icon.
 *
 * If the minimap is currently enabled (`minimap_visible`), this function:
 * - Computes the size of each tile using `get_tile_size`.
 * - Computes the player's icon radius based on `PLAYER_SCALE`.
 * - Draws all wall tiles with `draw_minimap_walls`.
 * - Draws the player icon with `draw_player_on_minimap`.
 *
 * This provides the player with a top-down view of their surroundings.
 *
 * @param game Pointer to the game state (includes map, player, and buffer).
 */
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
