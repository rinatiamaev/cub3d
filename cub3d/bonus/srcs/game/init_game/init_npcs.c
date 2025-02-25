/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:54:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 00:16:04 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void update_npcs_list(t_game *game, t_npc *npc)
{
	game->npcs = x_realloc(game, game->npcs,
			game->npc_count * sizeof(t_npc *),
			(game->npc_count + 1) * sizeof(t_npc *));
	game->npcs[game->npc_count] = npc;
	game->npc_count++;
}

static void	init_npc_frames_and_animation(t_game *game, t_npc *npc)
{
	struct timeval	tv;
	int				i;
	
	load_npc_frames(game, npc);
	i = 0;
	while (i < npc->num_frames)
		npc->idle_frames[i++].size = npc->size;
	gettimeofday(&tv, NULL);
	npc->anim_start = tv.tv_sec * 1000000L + tv.tv_usec;
}

void spawn_witch_kitty(t_game *game, double x, double y)
{
	t_npc *npc;
	static char *frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6, WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};

	npc = x_calloc(game, 1, sizeof(t_npc));
	*npc = (t_npc){
		.pos = (t_dpoint){x + 0.5, y + 0.5},
		.type = "witch_kitty",
		.paths = frames,
		.num_frames = sizeof(frames) / sizeof(frames[0]),
		.size = (t_point){64, 64}
	};
	init_npc_frames_and_animation(game, npc);
	update_npcs_list(game, npc);
}
