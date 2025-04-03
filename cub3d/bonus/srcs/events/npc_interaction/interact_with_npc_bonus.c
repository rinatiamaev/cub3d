/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_npc_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:09:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:34:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Finds the closest NPC within a specified range and in front
 *        of the player.
 *
 * Iterates through all NPCs and returns the one that is both closest
 * (within `max_distance`) and within the player's field of view.
 *
 * @param game Pointer to the game structure.
 * @param max_distance Maximum distance to consider for NPC interaction.
 * @return Pointer to the closest valid NPC, or NULL if none found.
 */
t_npc	*find_closest_npc(t_game *game, double max_distance)
{
	t_npc	*closest_npc;
	double	closest_dist;
	double	current_dist;
	int		i;

	closest_npc = NULL;
	closest_dist = max_distance;
	i = 0;
	while (i < game->npc_count)
	{
		current_dist
			= ft_euclidean_dist_dpoint(game->player.pos, game->npcs[i]->pos);
		if (current_dist < closest_dist
			&& is_facing_target(&game->player, game->npcs[i]->pos))
		{
			closest_dist = current_dist;
			closest_npc = game->npcs[i];
		}
		i++;
	}
	return (closest_npc);
}

/**
 * @brief Handles interaction with an NPC.
 *
 * If the closest NPC is in the CHASE state and the player has water,
 * it triggers a splash to stop the NPC. Otherwise, it initiates dialogue
 * with the NPC if possible.
 *
 * @param game Pointer to the game structure.
 * @return true if interaction was successful or initiated, false otherwise.
 */
bool	interact_with_npc(t_game *game)
{
	if (!handle_npc_chase(game))
		return (false);
	return (handle_npc_dialogue(game));
}
