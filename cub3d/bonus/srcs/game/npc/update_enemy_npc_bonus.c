/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy_npc_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:06:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:47:37 by nlouis           ###   ########.fr       */
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
	return (ft_euclidean_dist_dpoint(player->pos, npc->pos) < range);
}

/**
 * @brief Resets the animation index and timer for an NPC sprite.
 *
 * This function is typically called when the NPC's state changes,
 * to restart the animation from the beginning and ensure smooth transitions.
 *
 * @param npc Pointer to the NPC whose animation should be reset.
 */
static void	reset_animations(t_npc *npc)
{
	npc->sprite.anim_index = 0;
	npc->sprite.anim_timer = 0.0;
}

/**
 * @brief Updates the state of an enemy NPC based on the player's position.
 *
 * This function evaluates the NPC's proximity to the player, line of sight,
 * and whether the player is facing the NPC. Based on these conditions, the NPC
 * state is updated to either CHASE or PATROL. If the NPC has been hit,
 * its state is forcibly set to HIT.
 *
 * If the state changes from the previous one, the NPC's animation is reset.
 *
 * @param game Pointer to the game structure containing the map and player.
 * @param npc Pointer to the NPC whose state is being updated.
 * @param player Pointer to the player to evaluate proximity and line of sight.
 */
static void	update_npc_state(t_game *game, t_npc *npc, t_player *player)
{
	t_npc_state	previous_state;

	previous_state = npc->state;
	if (is_player_near_npc(npc, player, 5.0)
		|| has_line_of_sight(game, npc->pos, player->pos)
		|| is_facing_target(&game->player, npc->pos))
		npc->state = CHASE;
	else
		npc->state = PATROL;
	if (npc->is_hit)
		npc->state = HIT;
	if (npc->state != previous_state)
		reset_animations(npc);
}

/**
 * @brief Updates the behavior and animation of an enemy NPC (e.g., fire spirit).
 *
 * This function determines the current state of the NPC based on proximity,
 * line of sight, or being hit. It then performs the appropriate update based
 * on the state:
 * - PATROL: Idle animation and path patrol logic.
 * - CHASE: Idle animation and follow logic. Ends game if player is too close.
 * - HIT: Hit animation and timer; resets behavior after the duration ends.
 *
 * @param game Pointer to the game context.
 * @param npc Pointer to the enemy NPC to update.
 * @param delta_time Time elapsed since the last frame, used for animations.
 */
void	update_enemy_npc(t_game *game, t_npc *npc, double delta_time)
{
	update_npc_state(game, npc, &game->player);
	if (npc->state == PATROL)
	{
		play_fire_spirit_idle_animation(npc, delta_time);
		move_npc_patrol(game, npc, delta_time);
	}
	else if (npc->state == CHASE)
	{
		play_fire_spirit_idle_animation(npc, delta_time);
		move_npc_follow(game, npc, delta_time);
		if (is_player_near_npc(npc, &game->player, 0.8))
			game->state = GAME_OVER;
	}
	else if (npc->state == HIT)
	{
		play_fire_spirit_hit_animation(npc, delta_time);
		npc->hit_timer += delta_time;
		if (npc->hit_timer >= npc->hit_duration)
		{
			npc->hit_timer = 0.0;
			change_fire_spirit_behavior(game, npc);
		}
	}
}
