/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_witch_kitty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 02:43:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "witch_kitty_dialogues.h"

void	init_witch_kitty_dialogues(t_game *game, t_npc *npc)
{
	static char	*witch_kitty_dialogues[][10] = {
	{WKD_0_0, NULL},
	{WKD_1_0, WKD_1_1, WKD_1_2, WKD_1_3, WKD_1_4, WKD_1_5, WKD_1_6, NULL},
	{WKD_2_0, WKD_2_1, WKD_2_2, WKD_2_3, WKD_2_4, NULL},
	{WKD_3_0, WKD_3_1, WKD_3_2, NULL},
	{WKD_4_0, WKD_4_1, WKD_4_2, WKD_4_3, NULL},
	{WKD_5_0, WKD_5_1, WKD_5_2, WKD_5_3, WKD_5_4, NULL},
	{WKD_6_0, WKD_6_1, WKD_6_2, NULL},
	{WKD_7_0, WKD_7_1, WKD_7_2, WKD_7_3, NULL},
	{NULL}
	};

	npc->dialogue.phase_count
		= sizeof(witch_kitty_dialogues) / sizeof(witch_kitty_dialogues[0]);
	allocate_dialogues
		(game, &npc->dialogue, witch_kitty_dialogues,
			npc->dialogue.phase_count);
}

static void	init_witch_kitty_sprites(t_npc *npc)
{
	static char	*idle_frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6, WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};
	static char	*move_frames[] = {
		WK_WAWAY0, WK_WAWAY1, WK_WAWAY2, WK_WAWAY3,
		WK_WTOW0, WK_WTOW1, WK_WTOW2, WK_WTOW3,
		WK_WLEFT0, WK_WLEFT1, WK_WLEFT2, WK_WLEFT3,
		WK_WRI0, WK_WRI1, WK_WRI2, WK_WRI3
	};
	static char	*speak_frames[] = {
		WK_C0, WK_C1, WK_C2, WK_C3, WK_C4, WK_C5,
		WK_C6, WK_C7, WK_C8, WK_C9, WK_C10, WK_C11
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

static void	init_witch_kitty(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->type = "kitty";
	npc->name = "witch kitty";
	npc->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	npc->speed = 1.2;
	npc->following_speed = 2.5;
	init_npc_pathfinding(game, npc);
	generate_npc_waypoints(npc, game);
	init_witch_kitty_sprites(npc);
	init_npc_animation(game, &npc->sprite);
	init_witch_kitty_dialogues(game, npc);
}

void	spawn_witch_kitty(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	init_witch_kitty(game, npc, pos);
	update_npc_list(game, npc);
}
