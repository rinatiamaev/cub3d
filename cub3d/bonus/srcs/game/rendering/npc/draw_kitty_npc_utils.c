/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kitty_npc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:08:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 20:28:58 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * Returns the current movement angle of the NPC.
 * Falls back to the last known direction if NPC is idle.
 */
static double	get_npc_movement_angle(t_npc *npc)
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
 * Returns the angle from the NPC to the player.
 */
static double	get_angle_to_player(t_npc *npc, t_player *player)
{
	return (get_vector_angle_between(npc->pos, player->pos));
}

/**
 * Maps a degree angle to a corresponding walk animation direction.
 */
static int	get_direction_from_angle(double degrees)
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
 * Computes the walk direction of the NPC relative to the player.
 * Used to choose which animation to display (toward, away, side).
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
