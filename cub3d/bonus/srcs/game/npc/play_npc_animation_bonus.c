/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_npc_animation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:19:32 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:21:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Plays the NPC's movement animation.
 *
 * Updates the animation timer and cycles through the movement frames
 * at a fixed speed. Assumes a 4-frame movement cycle.
 *
 * @param npc Pointer to the NPC whose animation is updated.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	play_movement_animation(t_npc *npc, double delta_time)
{
	const double	anim_speed = 200.0;

	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= anim_speed)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index = (npc->sprite.anim_index + 1) % 4;
	}
}

/**
 * @brief Plays the NPC's idle (wait) animation.
 *
 * Advances through the idle frames based on a timer.
 * Loops back to the first frame after the last one.
 *
 * @param npc Pointer to the NPC whose animation is updated.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	play_wait_animation(t_npc *npc, double delta_time)
{
	const double	anim_speed = 200.0;

	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= anim_speed)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index++;
		if (npc->sprite.anim_index >= npc->sprite.idle_frames_count)
			npc->sprite.anim_index = 0;
	}
}

/**
 * @brief Plays the NPC's speaking animation.
 *
 * Cycles through the speaking frames based on elapsed time.
 * Loops back when the last frame is reached.
 *
 * @param npc Pointer to the NPC whose animation is updated.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	play_speak_animation(t_npc *npc, double delta_time)
{
	const double	anim_speed = 200.0;

	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= anim_speed)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index++;
		if (npc->sprite.anim_index >= npc->sprite.speak_frames_count)
			npc->sprite.anim_index = 0;
	}
}

/**
 * @brief Plays the fire spirit's idle animation.
 *
 * Updates the animation for idle state with a slower speed than other NPCs,
 * because it has less frames.
 *
 * @param npc Pointer to the fire spirit NPC.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	play_fire_spirit_idle_animation(t_npc *npc, double delta_time)
{
	const double	anim_speed = 300.0;

	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= anim_speed)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index++;
		if (npc->sprite.anim_index >= npc->sprite.idle_frames_count)
			npc->sprite.anim_index = 0;
	}
}

/**
 * @brief Plays the fire spirit's hit animation.
 *
 * Cycles through the hit frames used when the spirit takes damage.
 *
 * @param npc Pointer to the fire spirit NPC.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	play_fire_spirit_hit_animation(t_npc *npc, double delta_time)
{
	const double	anim_speed = 300.0;

	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= anim_speed)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index++;
		if (npc->sprite.anim_index >= npc->sprite.hit_frames_count)
			npc->sprite.anim_index = 0;
	}
}
