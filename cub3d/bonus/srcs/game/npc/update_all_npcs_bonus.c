/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_all_npcs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:46:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:53:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Allows an NPC to interact with a nearby door.
 *
 * This function checks whether the NPC is within interaction range of any
 * door in the game. If a door is found within a certain distance threshold,
 * and it is currently closed, the door is set to the opening state.
 *
 * This is primarily used when NPCs in the FOLLOW state need to pass through
 * doors that are in their way.
 *
 * @param game Pointer to the game context containing doors.
 * @param npc Pointer to the NPC trying to interact with doors.
 * @return true if a door was found and interacted with, false otherwise.
 */
static bool	npc_interact_with_door(t_game *game, t_npc *npc)
{
	t_door	*door;
	double	range;
	int		i;
	double	current_distance;

	door = NULL;
	range = 1.5;
	i = 0;
	while (i < game->door_count)
	{
		current_distance = ft_cab_dist_dpoint(npc->pos, game->doors[i]->pos);
		if (current_distance <= range)
		{
			door = game->doors[i];
			break ;
		}
		i++;
	}
	if (!door)
		return (false);
	if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENING;
	return (true);
}

/**
 * @brief Updates all NPCs, handling both friendly and enemy behaviors.
 *
 * This function iterates through the list of all NPCs and updates
 * each one according to its type:
 *
 * - Friendly NPCs: Their state and animation are updated with `update_npc`.
 *   If they are in the FOLLOW state, they may automaticaly open doors
 *   via `npc_interact_with_door`.
 * - Enemy NPCs: Their behavior is updated using `update_enemy_npc`.
 *
 * This function ensures each NPC behaves accordingly in real-time, depending
 * on its proximity to the player and other game conditions.
 *
 * @param game Pointer to the game state.
 * @param delta_time Time elapsed since the last update, used for animations
 *                   and movement.
 */
void	update_all_npcs(t_game *game, double delta_time)
{
	t_npc	*npc;
	int		i;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (!npc->is_enemy)
		{
			update_npc(game, npc, delta_time);
			if (npc->state == FOLLOW)
				npc_interact_with_door(game, npc);
		}
		else
			update_enemy_npc(game, npc, delta_time);
		i++;
	}
}
