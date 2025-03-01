/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_witch_kitty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/01 01:18:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_witch_kitty_waypoints(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->waypoint_count = 4;
	npc->waypoints = x_calloc(game, 1, npc->waypoint_count * sizeof(t_dpoint));
	npc->waypoints[0] = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	npc->waypoints[1] = (t_dpoint){pos.x + 3.5, pos.y + 0.5};
	npc->waypoints[2] = (t_dpoint){pos.x + 3.5, pos.y + 3.5};
	npc->waypoints[3] = (t_dpoint){pos.x + 0.5, pos.y + 3.5};
	npc->current_wp = 1;
	npc->threshold_dist = 0.1;
}

static void	init_witch_kitty(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->pos.x = pos.x + 0.5;
	npc->pos.y = pos.y + 0.5;
	npc->speed = 1.0;
	init_witch_kitty_waypoints(game, npc, pos);
}

static void	init_witch_kitty_sprites(t_npc *npc)
{
	static char	*idle_frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6,
		WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};
	static char	*move_frames[] = {
		WK_WAWAY0, WK_WAWAY1, WK_WAWAY2, WK_WAWAY3,
		WK_WTOW0, WK_WTOW1, WK_WTOW2, WK_WTOW3,
		WK_WLEFT0, WK_WLEFT1, WK_WLEFT2, WK_WLEFT3,
		WK_WRI0, WK_WRI1, WK_WRI2, WK_WRI3
	};

	npc->sprite.type = "kitty";
	npc->sprite.size = (t_point){64, 64};
	npc->sprite.idle_paths = idle_frames;
	npc->sprite.num_idle_frames
		= sizeof(idle_frames) / sizeof(idle_frames[0]);
	npc->sprite.move_paths = move_frames;
	npc->sprite.move_frames_count
		= sizeof(move_frames) / sizeof(move_frames[0]);
}

void	spawn_witch_kitty(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	init_witch_kitty(game, npc, pos);
	init_witch_kitty_sprites(npc);
	init_sprite_frames_and_animation(game, &npc->sprite);
	update_npc_list(game, npc);
}
