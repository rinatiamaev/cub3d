/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_position_valid_player_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:13:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:07:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if a given position is blocked by map boundaries or a wall.
 *
 * Converts the floating-point position into grid coordinates and verifies
 * whether it is outside the map boundaries or inside a wall tile.
 *
 * @param game Pointer to the game structure.
 * @param pos The position to check.
 * @return true if the position is blocked, false otherwise.
 */
static bool	is_blocked(t_game *game, t_dpoint pos)
{
	t_point	grid_pos;

	grid_pos = (t_point){(int)pos.x, (int)pos.y};
	return (!is_within_bounds(game, grid_pos) || is_wall(game, grid_pos));
}

/**
 * @brief Checks if the player's position is valid and not too close to walls.
 *
 * This function verifies if the given position is not blocked by a wall or
 * out of bounds. It also performs extra checks around the position with
 * small offsets to avoid getting stuck near walls or the player to be able to
 * move through corners.
 *
 * @param game Pointer to the game structure.
 * @param pos The position to validate.
 * @return true if the position is valid, false otherwise.
 */
bool	is_map_position_valid_player(t_game *game, t_dpoint pos)
{
	t_dpoint	checks[4];
	int			i;

	if (is_blocked(game, pos))
		return (false);
	checks[0] = (t_dpoint){pos.x - 0.1, pos.y};
	checks[1] = (t_dpoint){pos.x + 0.1, pos.y};
	checks[2] = (t_dpoint){pos.x, pos.y - 0.1};
	checks[3] = (t_dpoint){pos.x, pos.y + 0.1};
	i = 0;
	while (i < 4)
	{
		if (is_blocked(game, checks[i]))
			return (false);
		i++;
	}
	return (true);
}
