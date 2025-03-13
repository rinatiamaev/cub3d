/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_position_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:12:02 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 16:23:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_door_walkable(t_game *game, t_point pos)
{
	t_door	*door;

	if (game->map->matrix[pos.y][pos.x] != DOOR)
		return (true);
	door = find_door_at(game, pos);
	return (door && door->state == DOOR_OPEN);
}

static bool	is_wall(t_game *game, t_point pos)
{
	return (game->map->matrix[(int)(pos.y)][(int)pos.x] == WALL);
}

bool	is_map_position_valid(t_game *game, t_dpoint pos)
{
	t_point			grid_pos;

	grid_pos = (t_point){(int)pos.x, (int)pos.y};
	if (is_wall(game, grid_pos))
		return (false);
	if (!is_within_bounds(game, grid_pos))
		return (false);
	if (!is_door_walkable(game, grid_pos))
		return (false);
	return (true);
}
