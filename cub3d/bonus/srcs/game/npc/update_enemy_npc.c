/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy_npc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:06:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 22:00:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_player_near_npc(t_npc *npc, t_player *player, double range)
{
	return (ft_cab_dist_dpoint(player->pos, npc->pos) < range);
}

static void	reset_animations(t_npc *npc)
{
	npc->sprite.anim_index = 0;
	npc->sprite.anim_timer = 0.0;
}

static void	update_npc_state(t_game *game, t_npc *npc, t_player *player)
{
	t_npc_state previous_state;

	previous_state = npc->state;
	if (is_player_near_npc(npc, player, 8.0)
		&& has_line_of_sight(game, npc, player))
		npc->state = NPC_STATE_CHASE;
	else
	{
		if (npc->is_hit)
			npc->state = NPC_STATE_HIT;
		else
			npc->state = NPC_STATE_PATROL;
	}
	if (npc->state != previous_state)
		reset_animations(npc);
}


void	update_enemy_npc(t_game *game, t_npc *npc, double delta_time)
{
	update_npc_state(game, npc, &game->player);
	if (npc->state == NPC_STATE_PATROL)
	{
		play_fire_spirit_idle_animation(npc, delta_time);
		move_npc_patrol(game, npc, delta_time);
	}
	else if (npc->state == NPC_STATE_CHASE)
	{
		play_fire_spirit_idle_animation(npc, delta_time);
		move_npc_follow(game, npc, delta_time);
		if (is_player_near_npc(npc, &game->player, 0.5))
			game->state = GAME_OVER;
	}
	else if (npc->state == NPC_STATE_HIT)
	{
		play_fire_spirit_hit_animation(npc, delta_time);
		change_fire_spirit_behavior(game, &npc);
	}
}
