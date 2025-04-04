/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:23:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:17:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if an NPC has reached its target position.
 *
 * Compares the distance between the NPC's current position and the target.
 * If the distance is smaller than the NPC's configured threshold, the target
 * is considered reached.
 *
 * Uses cab distance (a.k.a. Manhattan distance) which is less expensive
 * to compute and often good enough for simple proximity checks.
 *
 * @param npc Pointer to the NPC.
 * @param target The target position the NPC is moving toward.
 * @return true if the target has been reached, false otherwise.
 */
static bool	has_reached_target(t_npc *npc, t_dpoint target)
{
	double	distance_to_target;

	distance_to_target = ft_cab_dist_dpoint(npc->pos, target);
	return (distance_to_target < npc->threshold_dist);
}

/**
 * @brief Stops the NPC at the specified target position.
 *
 * This function sets the NPC's position to the target coordinates and
 * resets its movement vector to zero, effectively stopping its movement.
 *
 * @param npc Pointer to the NPC to stop.
 * @param target The target position where the NPC should stop.
 */
static void	stop_npc(t_npc *npc, t_dpoint target)
{
	npc->pos.x = target.x;
	npc->pos.y = target.y;
	npc->move_vec = (t_dpoint){0, 0};
}

/**
 * @brief Determines whether the NPC should stop moving toward its target.
 *
 * This function checks several conditions that may require the NPC to stop:
 * - The NPC has been hit (e.g., by the player using water).
 * - Another NPC is currently engaged in dialogue with the player.
 * - The NPC has reached its target position (within a small threshold).
 *
 * @param game Pointer to the game state.
 * @param npc Pointer to the NPC being evaluated.
 * @param target The destination the NPC is moving toward.
 * @return true if the NPC should stop; false otherwise.
 */
static bool	should_stop_npc(t_game *game, t_npc *npc, t_dpoint target)
{
	if (npc->is_hit)
		return (true);
	if (is_any_npc_talking(game))
		return (true);
	if (has_reached_target(npc, target))
		return (true);
	return (false);
}

/**
 * @brief Retrieves the current speed of the NPC.
 *
 * This function checks if the NPC is currently following another entity
 * and returns the appropriate speed based on that condition.
 *
 * @param npc Pointer to the NPC whose speed is being queried.
 * @return The current speed of the NPC.
 */
static double	get_current_speed(t_npc *npc)
{
	if (npc->is_following)
		return (npc->following_speed);
	return (npc->speed);
}

/**
 * @brief Moves an NPC towards a given target position.
 *
 * This function computes the direction to the target and updates the NPC's
 * position based on its movement speed and delta time. It also checks for
 * various conditions under which the NPC should stop moving.
 *
 * @details
 * The NPC will stop moving if:
 * - It has been hit (e.g., splashed by the player).
 * - Any NPC is currently talking to the player.
 * - It has reached the target position (within a threshold distance).
 *
 * When stopping due to reaching the target, its position is snapped
 * exactly to the target, and its movement vector is reset.
 *
 * @param game Pointer to the game state.
 * @param npc Pointer to the NPC to move.
 * @param target The target position the NPC should move toward.
 * @param delta_time The time delta (in seconds) since the last frame.
 * @return true if the NPC has stopped moving; false otherwise.
 */
bool	move_npc(t_game *game, t_npc *npc, t_dpoint target, double delta_time)
{
	double		current_speed;
	double		step;

	if (should_stop_npc(game, npc, target))
	{
		if (has_reached_target(npc, target))
			stop_npc(npc, npc->pos);
		return (true);
	}
	current_speed = get_current_speed(npc);
	npc->move_vec = get_unit_direction_vector(npc->pos, target);
	step = current_speed * delta_time;
	npc->pos.x += npc->move_vec.x * step;
	npc->pos.y += npc->move_vec.y * step;
	return (false);
}
