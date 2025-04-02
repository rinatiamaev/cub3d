/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:46:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 22:07:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Spawns a normal door at the specified map coordinates.
 *
 * This function allocates and initializes a new door entity with default
 * parameters (closed state, normal type, speed of 1.0) and adds it to
 * the game's list of doors.
 *
 * The door is positioned using floating-point coordinates, which allows
 * for sub-tile precision.
 *
 * @param game Pointer to the game state.
 * @param x X-coordinate (in map space) where the door should be placed.
 * @param y Y-coordinate (in map space) where the door should be placed.
 */
void	spawn_door(t_game *game, double x, double y)
{
	t_door		*door;

	door = x_calloc(game, 1, sizeof(t_door));
	door->pos = (t_dpoint){x, y};
	door->type = NORMAL_DOOR;
	door->state = DOOR_CLOSED;
	door->speed = 1.0;
	update_door_list(game, door);
}
