/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_door_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:01:35 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 22:08:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Adds a new door to the game's dynamic list of doors.
 *
 * This function reallocates the door array to accommodate one more door,
 * stores the given door at the end of the array, and increments the total
 * door count.
 *
 * Memory reallocation is handled via `x_realloc`, which exits the game on
 * failure.
 *
 * @param game Pointer to the game state.
 * @param door Pointer to the newly created door to be added.
 */
void	update_door_list(t_game *game, t_door *door)
{
	game->doors = x_realloc(game, game->doors,
			game->door_count * sizeof(t_door *),
			(game->door_count + 1) * sizeof(t_door *));
	game->doors[game->door_count] = door;
	game->door_count++;
}
