/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_door_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:11:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:41:30 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Finds the closest door in range and in the player's view direction.
 *
 * Iterates over all doors and returns the closest one within the specified
 * range and field of view (based on facing direction). Returns NULL if no
 * such door is found.
 *
 * @param game Pointer to the game structure.
 * @param range Maximum search distance.
 * @return Pointer to the closest door if found, NULL otherwise.
 */
t_door	*find_closest_door(t_game *game, double range)
{
	t_door	*closest_door;
	double	min_distance;
	double	current_distance;
	int		i;

	closest_door = NULL;
	min_distance = range;
	i = 0;
	while (i < game->door_count)
	{
		current_distance
			= ft_euclidean_dist_dpoint(game->player.pos, game->doors[i]->pos);
		if (current_distance <= min_distance
			&& is_facing_target(&game->player, game->doors[i]->pos))
		{
			min_distance = current_distance;
			closest_door = game->doors[i];
		}
		i++;
	}
	return (closest_door);
}

/**
 * @brief Handles interaction between the player and the nearest door.
 *
 * Finds the closest door within a 2.0 unit range and checks if it is locked.
 * If the player has a key, the door is unlocked and the key is consumed.
 * Displays a message accordingly.
 *
 * @param game Pointer to the game structure.
 * @return true if a door was found and interaction attempted, false otherwise.
 */
bool	interact_with_door(t_game *game)
{
	t_door	*door;

	door = find_closest_door(game, 2.0);
	if (!door)
		return (false);
	if (door->state == DOOR_LOCKED)
	{
		if (game->player.has_key)
		{
			door->state = DOOR_CLOSED;
			game->player.has_key = false;
			show_temp_message(game, 3.0, "You unlocked the door!");
		}
		else
			show_temp_message(game, 3.0, "The door is locked!");
	}
	return (true);
}
