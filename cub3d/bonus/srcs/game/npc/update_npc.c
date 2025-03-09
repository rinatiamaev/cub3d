/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:06:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 19:51:13 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void	play_patrol_animation(t_npc *npc, double delta_time)
{
	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= 200.0)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index = (npc->sprite.anim_index + 1) % 4;
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

/* if (!npc->sound_played)
{
	system("aplay ./bonus/assets/01.wav &");  // JUST FOR TESTING WE CANT USE system() call
	npc->sound_played = 1;
} */

static void update_npc_behavior(t_npc *npc, t_player *player)
{
	t_npc_state previous_state = npc->state;

	// If NPC is speaking, keep them in SPEAK mode
	if (npc->state == NPC_STATE_SPEAK)
		return ;

	// If FOLLOW is enabled
	if (npc->state == NPC_STATE_FOLLOW)
	{
		// If the player is standing still, NPC should WAIT
		if (npc->pos.x == player->last_pos.x && npc->pos.y == player->last_pos.y)
			npc->state = NPC_STATE_WAIT;
		else
			npc->state = NPC_STATE_FOLLOW; // Keep following
	}
	else
	{
		// Default behavior: Patrol if far, Wait if near
		if (is_player_near_npc(npc, player, 1.5))
			npc->state = NPC_STATE_WAIT;
		else
			npc->state = NPC_STATE_PATROL;
	}

	// If state changed, reset animations
	if (npc->state != previous_state)
	{
		npc->sprite.anim_index = 0;
		npc->sprite.anim_timer = 0.0;
	}
}



static void update_npc(t_game *game, t_npc *npc, double delta_time)
{
	update_npc_behavior(npc, &game->player);

	if (npc->state == NPC_STATE_SPEAK)
		play_speak_animation(npc, delta_time);
	else if (npc->state == NPC_STATE_WAIT)
		play_wait_animation(npc, delta_time);
	else if (npc->state == NPC_STATE_PATROL
			|| npc->state == NPC_STATE_FOLLOW)
	{
		play_patrol_animation(npc, delta_time);
		move_npc_plan(game, npc, delta_time);
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
