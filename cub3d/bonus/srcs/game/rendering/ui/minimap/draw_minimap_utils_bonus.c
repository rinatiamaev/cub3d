/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:43:45 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:18:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Calculates the size of a single tile on the minimap.
 *
 * This function determines the pixel size of one map tile on the minimap
 * based on the map's dimensions and the fixed `MINIMAP_SIZE`. It ensures
 * that all tiles fit within the minimap area by choosing the smaller
 * dimension between width and height.
 *
 * @param map Pointer to the map structure (provides map dimensions).
 * @return The computed tile size in pixels.
 */
int	get_tile_size(t_map *map)
{
	int	tile_width;
	int	tile_height;
	int	tile_size;

	tile_width = MINIMAP_SIZE / map->size.x;
	tile_height = MINIMAP_SIZE / map->size.y;
	tile_size = fmin(tile_width, tile_height);
	return (tile_size);
}

/**
 * @brief Converts a map grid coordinate to a screen-space position
 *        on the minimap.
 *
 * This function computes the top-left pixel position on the minimap where a
 * given map tile should be drawn. It applies the `tile_size` scaling and
 * adds fixed screen offsets (`MINIMAP_OFFSET_X` and `MINIMAP_OFFSET_Y`) to
 * correctly position the tile within the minimap area.
 *
 * @param map_pos The tile coordinates in the map grid.
 * @param tile_size The size of each tile in pixels.
 * @return The corresponding position in screen-space for the minimap.
 */
t_point	get_minimap_position(t_point map_pos, int tile_size)
{
	t_point	minimap_pos;
	t_point	offset;

	offset.x = map_pos.x * tile_size;
	offset.y = map_pos.y * tile_size;
	minimap_pos.x = MINIMAP_OFFSET_X + offset.x;
	minimap_pos.y = MINIMAP_OFFSET_Y + offset.y;
	return (minimap_pos);
}

/**
 * @brief Checks if a point lies within a circle of given radius.
 *
 * This function determines whether the `offset` point is within a
 * circle centered at the origin `(0, 0)` with the specified `radius`.
 * It uses the squared distance to avoid unnecessary square roots.
 *
 * Commonly used to render circular shapes, such as the player icon
 * on the minimap.
 *
 * @param offset The point offset from the center of the circle.
 * @param radius The radius of the circle.
 * @return true if the point is inside the circle, false otherwise.
 */
bool	is_point_in_circle(t_point offset, int radius)
{
	int	distance_squared;
	int	radius_squared;

	distance_squared = offset.x * offset.x + offset.y * offset.y;
	radius_squared = radius * radius;
	return (distance_squared <= radius_squared);
}
