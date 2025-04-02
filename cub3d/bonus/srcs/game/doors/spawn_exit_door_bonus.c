/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_exit_door_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:00:58 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 22:08:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Spawns a locked exit door at the specified position.
 *
 * This function allocates and initializes a special exit door with the
 * type `EXIT_DOOR_TYPE`, a locked state, and a default opening speed.
 * The door's position is stored in the game state's `exit_pos` for
 * easy reference in win condition checks.
 *
 * The door is then added to the game's door list.
 *
 * @param game Pointer to the game state.
 * @param x X-coordinate (in map space) of the exit door.
 * @param y Y-coordinate (in map space) of the exit door.
 */
void	spawn_exit_door(t_game *game, double x, double y)
{
	t_door		*door;

	door = x_calloc(game, 1, sizeof(t_door));
	door->pos = (t_dpoint){x, y};
	game->exit_pos = door->pos;
	door->type = EXIT_DOOR_TYPE;
	door->state = DOOR_LOCKED;
	door->speed = 1.0;
	update_door_list(game, door);
}
