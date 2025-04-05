/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fire_spirit_behavior_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:51:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/05 19:56:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes the dialogue lines for the fire spirit NPC.
 *
 * This function sets up a series of predefined dialogue phases for the
 * fire spirit. Each phase contains one or more lines of dialogue that 
 * reflect the spirit's current behavior or story progression.
 *
 * The dialogues are stored in a 2D array of strings, where each subarray
 * corresponds to a different phase of interaction. The function calculates
 * the number of phases and uses `allocate_dialogues` to copy them into the
 * NPC's dialogue structure.
 *
 * @param game Pointer to the main game structure.
 * @param npc Pointer to the NPC to assign the dialogues to.
 */
void	init_fire_spirit_dialogues(t_game *game, t_npc *npc)
{
	static char	*dialogues[][10] = {
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
	}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}
	};

	npc->dialogue.phase_count = sizeof(dialogues) / sizeof(dialogues[0]);
	allocate_dialogues
		(game, &npc->dialogue, dialogues, npc->dialogue.phase_count);
}

/**
 * @brief Initializes the sprite animation frames for the fire spirit NPC.
 *
 * This function sets up the frame paths for idle, move, and speak animations
 * using the same shared set of textures (`npc_frames`). It also assigns a 
 * default size to the sprite frames.
 *
 * @param npc Pointer to the NPC whose sprite data will be initialized.
 */
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

/**
 * @brief Initializes a fire spirit NPC with default parameters and assets.
 *
 * This function sets up the fire spirit's new identity, position, movement
 * behavior, pathfinding data, sprites, animations, and dialogues. It prepares
 * the NPC to be updated and rendered in the game loop.
 *
 * @param game Pointer to the game context (for asset loading and allocation).
 * @param npc Pointer to the NPC structure to initialize.
 * @param pos Initial position of the fire spirit (centered in the map cell).
 */
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

/**
 * @brief Frees and resets all relevant data of an NPC.
 *
 * This function clears memory associated with an NPC's waypoints, textures,
 * pathfinding structures (`path` and `astar`), and resets the animation state.
 * It then zeroes out the entire NPC structure to remove all residual data.
 *
 * @warning After this call, the NPC pointer contents are invalidated except
 * for memory allocation. Reinitialization is required to reuse the NPC.
 *
 * @param game Pointer to the game context (used for memory-managed cleanup).
 * @param npc Pointer to the NPC to reset.
 */
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

/**
 * @brief Resets and reinitializes a fire spirit NPC.
 *
 * This function is used to change the behavior of a fire spirit
 * by fully resetting its internal state and reinitializing it with the same
 * position. It frees existing waypoints, textures, and pathfinding data, then
 * re-applies its original initialization logic to reset behavior cleanly.
 *
 * @param game Pointer to the main game context.
 * @param npc Pointer to the NPC to reset and reinitialize.
 */
void	change_fire_spirit_behavior(t_game *game, t_npc *npc)
{
	t_dpoint	pos;

	pos = npc->pos;
	reset_npc(game, npc);
	init_fire_spirit(game, npc, pos);
}
