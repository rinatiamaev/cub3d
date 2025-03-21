/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fire_spirit_behavior.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:51:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/21 09:48:15 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_fire_spirit_dialogues(t_game *game, t_npc *npc)
{
	static char	*dialogues[][11] = {
	{"I have to keep calm and not burn everything...",
		"Aaaaahuuuummmmmmm...", NULL
	},
	{"Oh thanks for cooling me down!",
		"When I realized I was stuck in a labyrinth...",
		"I panicked and started to burn everything...",
		"I'm sorry for the mess...",
		"I'm a fire spirit, you see...",
		"I can't help it when I get too hot...",
		"I am going to look for a way out...",
		"If I find one, I'll let you know!", NULL
	},
	{"You found a way out!?",
		"Lead the way, I am right behind you!", NULL
	}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}
	};

	npc->dialogue.phase_count = sizeof(dialogues) / sizeof(dialogues[0]);
	allocate_dialogues
		(game, &npc->dialogue, dialogues, npc->dialogue.phase_count);
}

static void	init_fire_spirit_sprites(t_npc *npc)
{
	static char	*npc_frames[] = {
		FS_N0, FS_N1, FS_N2, FS_N3, FS_N4
	};

	npc->sprite.size = (t_point){50, 50};
	npc->sprite.idle_paths = npc_frames;
	npc->sprite.idle_frames_count
		= sizeof(npc_frames) / sizeof(npc_frames[0]);
	npc->sprite.move_paths = npc_frames;
	npc->sprite.move_frames_count
		= sizeof(npc_frames) / sizeof(npc_frames[0]);
	npc->sprite.speak_paths = npc_frames;
	npc->sprite.speak_frames_count
		= sizeof(npc_frames) / sizeof(npc_frames[0]);
}

static void	init_fire_spirit(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->type = "fireSpirit";
	npc->name = "fire spirit";
	npc->pos = pos;
	npc->state = PATROL;
	npc->speed = 2.0;
	npc->following_speed = 3.0;
	init_npc_pathfinding(game, npc);
	generate_npc_waypoints(npc, game);
	init_fire_spirit_sprites(npc);
	init_npc_animation(game, &npc->sprite);
	init_fire_spirit_dialogues(game, npc);
}

static void	reset_npc(t_game *game, t_npc *npc)
{
	free_npc_waypoints(npc);
	free_npc_textures(game, &npc->sprite);
	if (npc->path)
	{
		free(npc->path);
		npc->path = NULL;
	}
	if (npc->astar)
	{
		reset_astar_struct(game, npc->astar);
		free(npc->astar);
	}
	npc->sprite.anim_index = 0;
	npc->sprite.anim_timer = 0.0;
	npc = ft_memset(npc, 0, sizeof(t_npc));
}

void	change_fire_spirit_behavior(t_game *game, t_npc *npc)
{
	t_dpoint	pos;

	pos = npc->pos;
	reset_npc(game, npc);
	init_fire_spirit(game, npc, pos);
}
