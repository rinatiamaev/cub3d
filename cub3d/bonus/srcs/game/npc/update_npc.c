/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:06:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 02:10:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	play_movement_animation(t_npc *npc, double delta_time)
{
	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= 200.0)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index = (npc->sprite.anim_index + 1) % 4;
	}
}

static void	play_wait_animation(t_npc *npc, double delta_time)
{
	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= 200.0)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index++;
		if (npc->sprite.anim_index >= npc->sprite.num_idle_frames)
			npc->sprite.anim_index = 0;
	}
}

static void	play_speak_animation(t_npc *npc, double delta_time)
{
	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= 200.0)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index++;
		if (npc->sprite.anim_index >= npc->sprite.speak_frames_count)
			npc->sprite.anim_index = 0;
	}
}

static void	reset_animations(t_npc *npc)
{
	npc->sprite.anim_index = 0;
	npc->sprite.anim_timer = 0.0;
}

static void	update_npc_state(t_npc *npc, t_player *player)
{
	t_npc_state	previous_state;

	previous_state = npc->state;
	if (npc->state == NPC_STATE_SPEAK)
		return ;
	if (is_player_near_npc(npc, player, 1.5))
		npc->state = NPC_STATE_WAIT;
	else
	{
		if (npc->is_following)
			npc->state = NPC_STATE_FOLLOW;
		else
			npc->state = NPC_STATE_PATROL;
	}
	if (npc->state != previous_state)
		reset_animations(npc);
}

static void	update_npc(t_game *game, t_npc *npc, double delta_time)
{
	update_npc_state(npc, &game->player);
	if (npc->state == NPC_STATE_SPEAK)
		play_speak_animation(npc, delta_time);
	if (npc->state == NPC_STATE_WAIT)
		play_wait_animation(npc, delta_time);
	if (npc->state == NPC_STATE_PATROL)
	{
		play_movement_animation(npc, delta_time);
		move_npc_patrol(game, npc, delta_time);
	}
	if (npc->state == NPC_STATE_FOLLOW)
	{
		play_movement_animation(npc, delta_time);
		move_npc_follow(game, npc, delta_time);
	}
}

void	update_all_npcs(t_game *game, double delta_time)
{
	t_npc	*npc;
	int		i;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		update_npc(game, npc, delta_time);
		i++;
	}
}
