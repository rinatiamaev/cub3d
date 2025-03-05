/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:06:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 20:23:50 by nlouis           ###   ########.fr       */
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

static void	update_npc_behavior(t_npc *npc, t_player *player)
{
	if (is_player_near_npc(npc, player, 1.5))
	{
		npc->state = NPC_STATE_WAIT;
		system("aplay ./bonus/assets/01.wav &");  // JUST FOR TESTING WE CANT USE system() call
	}
	else
		npc->state = NPC_STATE_PATROL;
}

static void	update_npc(t_game *game, t_npc *npc, double delta_time)
{
	update_npc_behavior(npc, &game->player);
	if (npc->state == NPC_STATE_WAIT)
		play_wait_animation(npc, delta_time);
	else if (npc->state == NPC_STATE_PATROL)
	{
		play_patrol_animation(npc, delta_time);
		move_npc_patrol(game, npc, delta_time);
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
