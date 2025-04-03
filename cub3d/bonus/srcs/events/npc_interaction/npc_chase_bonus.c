/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_chase_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:16:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:15:43 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Triggers the splash animation for the player.
 *
 * Resets the splash animation timer and index, and sets the splash flag
 * to true. This is typically called when the player uses water on an enemy.
 *
 * @param player Pointer to the player structure.
 */
static void	trigger_splash_animation(t_player *player)
{
	player->is_splashing = true;
	player->sprite.anim_index = 0;
	player->sprite.anim_timer = 0.0;
}

/**
 * @brief Handles the logic for splashing water on an aggressive NPC.
 *
 * Checks if there is a nearby NPC in the CHASE state within a 4.0 unit range.
 * If the player has water, the NPC is marked as hit, the water is consumed,
 * and the player's splash animation is triggered. In this case, the function
 * returns false to indicate that the chase interaction took precedence.
 *
 * @param game Pointer to the game structure.
 * @return true if no splash occurred or the NPC wasn't chasing.
 * @return false if the splash occurred and the NPC was affected.
 */
bool	handle_npc_chase(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 4.0);
	if (npc && npc->state == CHASE
		&& game->player.has_water)
	{
		npc->is_hit = true;
		game->player.has_water = false;
		trigger_splash_animation(&game->player);
		return (false);
	}
	return (true);
}
