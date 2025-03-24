/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:43:45 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:23:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

bool	is_point_in_circle(t_point offset, int radius)
{
	int	distance_squared;
	int	radius_squared;

	distance_squared = offset.x * offset.x + offset.y * offset.y;
	radius_squared = radius * radius;
	return (distance_squared <= radius_squared);
}
