/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_calico_kitty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:05:57 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/21 11:41:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "calico_kitty_dialogues.h"

void	init_calico_kitty_dialogues(t_game *game, t_npc *npc)
{
	npc->dialogue.phase_count = sizeof(calico_kitty_dialogues) / sizeof(calico_kitty_dialogues[0]);
	allocate_dialogues(game, &npc->dialogue, calico_kitty_dialogues, npc->dialogue.phase_count);
}
static void	init_calico_kitty_sprites(t_npc *npc)
{
	static char	*idle_frames[] = {
		CK0, CK1, CK2, CK3, CK4, CK5, CK6, CK7, CK8, CK9, CK10, CK11, CK12
	};
	static char	*move_frames[] = {
		CK_WTOW0, CK_WTOW1, CK_WTOW2, CK_WTOW3,
		CK_WAWAY0, CK_WAWAY1, CK_WAWAY2, CK_WAWAY3,
		CK_WLEFT0, CK_WLEFT1, CK_WLEFT2, CK_WLEFT3,
		CK_WRI0, CK_WRI1, CK_WRI2, CK_WRI3
	};
	static char	*speak_frames[] = {
		CK_C0, CK_C1, CK_C2, CK_C3, CK_C4, CK_C5, CK_C6, CK_C7, CK_C8, CK_C9
	};

	npc->sprite.size = (t_point){64, 64};
	npc->sprite.idle_paths = idle_frames;
	npc->sprite.idle_frames_count
		= sizeof(idle_frames) / sizeof(idle_frames[0]);
	npc->sprite.move_paths = move_frames;
	npc->sprite.move_frames_count
		= sizeof(move_frames) / sizeof(move_frames[0]);
	npc->sprite.speak_paths = speak_frames;
	npc->sprite.speak_frames_count
		= sizeof(speak_frames) / sizeof(speak_frames[0]);
}

static void	init_calico_kitty(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->type = "kitty";
	npc->name = "calico kitty";
	npc->is_hit = false;
	npc->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	npc->speed = 1.2;
	npc->following_speed = 2.5;
	init_npc_pathfinding(game, npc);
	generate_npc_waypoints(npc, game);
	init_calico_kitty_sprites(npc);
	init_npc_animation(game, &npc->sprite);
	init_calico_kitty_dialogues(game, npc);
}

void	spawn_calico_kitty(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	init_calico_kitty(game, npc, pos);
	update_npc_list(game, npc);
}
