/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kitty_npc_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:08:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:37:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Computes the movement angle of the NPC based on its velocity.
 *
 * This function determines the direction in which the NPC is moving by
 * converting its movement vector into an angle (in radians). If the NPC is
 * currently moving, it updates and uses the current movement vector.
 * Otherwise, it retains the last known movement vector to maintain a valid
 * direction for animation continuity.
 *
 * The result is used to determine how the NPC is oriented relative to the
 * player for directional animation selection.
 *
 * @param npc Pointer to the NPC whose movement direction is calculated.
 * @return The angle of movement (in radians), based on the last known vector.
 */
static inline double	get_npc_movement_angle(t_npc *npc)
{
	t_dpoint	current;
	t_dpoint	last;
	bool		is_moving;
	double		angle;

	current = npc->move_vec;
	last = npc->last_move_vec;
	is_moving = (fabs(current.x) > 0.0001 || fabs(current.y) > 0.0001);
	if (is_moving)
		last = current;
	npc->last_move_vec = last;
	angle = get_vector_angle(last);
	return (angle);
}

/**
 * @brief Calculates the angle from the NPC to the player.
 *
 * This function computes the angle (in radians) between the NPC's position
 * and the player's position in the world. It uses `get_vector_angle_between`
 * to determine the direction the NPC would need to face to look directly at
 * the player.
 *
 * This angle is used for comparing against the NPC's movement direction to
 * determine relative orientation (e.g., walking toward, away, left, or right).
 *
 * @param npc Pointer to the NPC.
 * @param player Pointer to the player.
 * @return The angle in radians from the NPC to the player.
 */
static inline double	get_angle_to_player(t_npc *npc, t_player *player)
{
	return (get_vector_angle_between(npc->pos, player->pos));
}

/**
 * @brief Maps an angle in degrees to a directional movement block.
 *
 * This function converts an angle (in degrees) into one of four logical
 * movement directions relative to the player:
 *
 * - `WALK_TOWARD`: facing the player (0° ± 45°)
 * - `WALK_LEFT`: moving left relative to player (90° ± 45°)
 * - `WALK_AWAY`: walking away from the player (180° ± 45°)
 * - `WALK_RIGHT`: moving right relative to player (270° ± 45°)
 *
 * It uses a simple range check to determine which quadrant the angle falls in.
 *
 * @param degrees The angle difference between npc movement and player
 *                (in degrees)
 * @return The corresponding movement block (WALK_TOWARD, LEFT, RIGHT, AWAY).
 */
static inline int	get_direction_from_angle(double degrees)
{
	if (degrees >= 315.0 || degrees < 45.0)
		return (WALK_TOWARD);
	if (degrees >= 45.0 && degrees < 135.0)
		return (WALK_LEFT);
	if (degrees >= 135.0 && degrees < 225.0)
		return (WALK_AWAY);
	if (degrees >= 225.0 && degrees < 315.0)
		return (WALK_RIGHT);
	return (WALK_TOWARD);
}

/**
 * @brief Determines the NPC's relative movement direction to the player.
 *
 * This function compares the NPC's movement angle with the angle toward the
 * player to determine how the NPC is moving relative to the player:
 *
 * - Toward the player
 * - Away from the player
 * - Left of the player
 * - Right of the player
 *
 * It uses the angular difference between the movement direction and the
 * direction to the player, converting it from radians to degrees and applying
 * clamping based on `DEAD_ZONE` to avoid flickering when stationary or
 * slightly off-angle.
 *
 * The last valid direction is cached and reused if the angular difference is
 * too small (i.e., inside the dead zone).
 *
 * @param npc Pointer to the NPC.
 * @param player Pointer to the player.
 * @return The movement direction block (WALK_TOWARD, AWAY, LEFT, or RIGHT).
 */
int	get_walk_block(t_npc *npc, t_player *player)
{
	static int	last_direction = WALK_TOWARD;
	double		move_angle;
	double		to_player_angle;
	double		angle_diff_rad;
	double		angle_diff_deg;

	move_angle = get_npc_movement_angle(npc);
	to_player_angle = get_angle_to_player(npc, player);
	angle_diff_rad = wrap_angle(move_angle - to_player_angle);
	angle_diff_deg = rad_to_deg(angle_diff_rad);
	if (angle_diff_deg < 0)
		angle_diff_deg += 360.0;
	if (fabs(angle_diff_deg) < DEAD_ZONE)
		return (last_direction);
	last_direction = get_direction_from_angle(angle_diff_deg);
	return (last_direction);
}

/**
 * @brief Returns the base frame index for a given walk direction block.
 *
 * This function maps a movement direction (`walk_block`) to the starting
 * index of its corresponding animation frame set. Each direction is assumed
 * to have 4 animation frames laid out in the sprite's `move_frames` array.
 *
 * Frame layout (example):
 * - WALK_AWAY   → frames 0–3
 * - WALK_TOWARD → frames 4–7
 * - WALK_LEFT   → frames 8–11
 * - WALK_RIGHT  → frames 12–15
 *
 * @param walk_block Movement direction block (WALK_AWAY, TOWARD, etc.).
 * @return The base index for that direction's animation frames.
 */
int	get_walk_animation_base_index(int walk_block)
{
	if (walk_block == WALK_AWAY)
		return (0);
	else if (walk_block == WALK_TOWARD)
		return (4);
	else if (walk_block == WALK_LEFT)
		return (8);
	else
		return (12);
}
