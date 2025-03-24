/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_npc_animation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:19:32 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:30:08 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
