/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fire_spirit_behavior.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:51:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/12 01:37:30 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_fire_spirit_dialogue(t_npc *npc)
{
	static char	*fire_spirit_dialogue[] = {
		"Oh thanks for cooling me down!",
		"When I realized I was stuck in a labyrinth...",
		"I panicked and started to burn everything...",
		"I'm sorry for the mess...",
		"I'm a fire spirit, you see...",
		"I can't help it when I get too hot...",
		"I am going to look for a way out...",
		"if I find one, I'll let you know!"
	};

	npc->lines = fire_spirit_dialogue;
	npc->line_count = sizeof(fire_spirit_dialogue) / sizeof(char *);
	npc->current_line = 0;
}

static void	init_fire_spirit_sprites(t_npc *npc)
{
	static char	*npc_frames[] = {
		FS_N0, FS_N1, FS_N2, FS_N3, FS_N4
	};

	npc->sprite.size = (t_point){50, 50};
	npc->sprite.idle_paths = npc_frames;
	npc->sprite.num_idle_frames
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
	npc->is_hit = false;
	npc->is_enemy = false;
	npc->pos = pos;
	npc->state = PATROL;
	npc->speed = 1.4;
	npc->patrol_range = 10;
	npc->waypoint_count = 4;
	npc->current_wp = 1;
	npc->threshold_dist = 0.2;
	npc->astar = x_calloc(game, 1, sizeof(t_astar));
	npc->astar->direction[0] = (t_point){0, -1};
	npc->astar->direction[1] = (t_point){0, 1};
	npc->astar->direction[2] = (t_point){-1, 0};
	npc->astar->direction[3] = (t_point){1, 0};
	generate_npc_waypoints(npc, game);
	init_fire_spirit_sprites(npc);
	init_sprite_frames_and_animation(game, &npc->sprite);
	init_fire_spirit_dialogue(npc);
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
