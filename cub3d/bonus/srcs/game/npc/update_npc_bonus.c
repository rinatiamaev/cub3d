/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:06:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:52:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if the player is within a certain distance of the NPC.
 *
 * This function computes the Euclidean distance between the NPC and the player
 * and compares it to a specified range threshold. It is typically used to 
 * trigger state changes like chasing or initiating dialogue.
 *
 * @param npc Pointer to the NPC.
 * @param player Pointer to the player.
 * @param range The maximum allowed distance between player and NPC.
 * @return true if the player is within range, false otherwise.
 */
static bool	is_player_near_npc(t_npc *npc, t_player *player, double range)
{
	return (ft_cab_dist_dpoint(player->pos, npc->pos) < range);
}

/**
 * @brief Resets the animation and pathfinding state of an NPC.
 *
 * This function resets the animation index and timer to restart animation from
 * the beginning. It also clears the curent navigation path (if any), resetting
 * path-related values like length and index. This is typically called when the
 * NPC changes state (from PATROL to FOLLOW).
 *
 * @param npc Pointer to the NPC whose animation and pathfinding data are reset.
 */
static void	reset_animations_and_path(t_npc *npc)
{
	npc->sprite.anim_index = 0;
	npc->sprite.anim_timer = 0.0;
	if (npc->path)
	{
		free(npc->path);
		npc->path = NULL;
		npc->path_length = 0;
		npc->path_index = 0;
	}
}

/**
 * @brief Updates the state of a NPC based on its interaction with the player.
 *
 * This function determines whether the NPC should switch between different
 * behavior states: `WAIT` (if the player is near), `FOLLOW` (if the NPC is
 * currently following), or `PATROL` (default state). If the NPC is currently
 * speaking (`SPEAK`), its state is not updated.
 *
 * When the state changes, the NPC's animation and pathfinding data are reset
 * to avoid inconsistencies in behavior or visuals.
 *
 * @param npc Pointer to the NPC whose state is being updated.
 * @param player Pointer to the player, used to evaluate proximity.
 */
static void	update_npc_state(t_npc *npc, t_player *player)
{
	t_npc_state	previous_state;

	previous_state = npc->state;
	if (npc->state == SPEAK)
		return ;
	if (is_player_near_npc(npc, player, 2.0))
		npc->state = WAIT;
	else
	{
		if (npc->is_following)
		{
			npc->state = FOLLOW;
		}
		else
			npc->state = PATROL;
	}
	if (npc->state != previous_state)
		reset_animations_and_path(npc);
}

/**
 * @brief Updates behavior and animation of a NPC based on its current state.
 *
 * This function first updates the NPC's state (WAIT, PATROL, FOLLOW, SPEAK)
 * depending on its proximity to the player and internal conditions
 * (`is_following`). Then, based on the updated state, it handles the
 * corresponding animation and logic:
 * 
 * - SPEAK: Plays the speaking animation.
 * - WAIT: Plays idle animation.
 * - PATROL: Plays movement animation and updates patrol pathfinding.
 * - FOLLOW: Plays movement animation and moves toward the player.
 *
 * @param game Pointer to the game state.
 * @param npc Pointer to the NPC to update.
 * @param delta_time Time elapsed since the last update, used for animations
 *        and movement.
 */
void	update_npc(t_game *game, t_npc *npc, double delta_time)
{
	update_npc_state(npc, &game->player);
	if (npc->state == SPEAK)
		play_speak_animation(npc, delta_time);
	else if (npc->state == WAIT)
		play_wait_animation(npc, delta_time);
	else if (npc->state == PATROL)
	{
		play_movement_animation(npc, delta_time);
		move_npc_patrol(game, npc, delta_time);
	}
	else if (npc->state == FOLLOW)
	{
		play_movement_animation(npc, delta_time);
		move_npc_follow(game, npc, delta_time);
	}
}
