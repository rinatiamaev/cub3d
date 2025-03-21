/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_fire_spirit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:51:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/21 09:49:16 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_fire_spirit_sprites(t_npc *npc)
{
	static char	*enemy_frames[] = {
		FS0, FS1, FS2, FS3, FS4
	};
	static char	*hit_frames[] = {
		FS_H0, FS_H1, FS_H2
	};

	npc->sprite.size = (t_point){50, 50};
	npc->sprite.idle_paths = enemy_frames;
	npc->sprite.idle_frames_count
		= sizeof(enemy_frames) / sizeof(enemy_frames[0]);
	npc->sprite.move_paths = enemy_frames;
	npc->sprite.move_frames_count
		= sizeof(enemy_frames) / sizeof(enemy_frames[0]);
	npc->sprite.speak_paths = enemy_frames;
	npc->sprite.speak_frames_count
		= sizeof(enemy_frames) / sizeof(enemy_frames[0]);
	npc->sprite.hit_paths = hit_frames;
	npc->sprite.hit_frames_count
		= sizeof(hit_frames) / sizeof(hit_frames[0]);
}

static void	init_fire_spirit(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->type = "fireSpirit";
	npc->name = "fire spirit";
	npc->is_enemy = true;
	npc->hit_duration = 2.0;
	npc->state = PATROL;
	npc->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	npc->speed = 3.0;
	init_npc_pathfinding(game, npc);
	generate_npc_waypoints(npc, game);
	init_fire_spirit_sprites(npc);
	init_npc_animation(game, &npc->sprite);
}

void	spawn_fire_spirit(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	init_fire_spirit(game, npc, pos);
	update_npc_list(game, npc);
}
