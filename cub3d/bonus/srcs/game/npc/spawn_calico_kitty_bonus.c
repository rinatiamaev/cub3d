/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_calico_kitty_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:05:57 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:37:35 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes the dialogue lines for the calico kitty NPC.
 *
 * This function defines a set of prewritten dialogue lines organized by
 * phases for the calico kitty character. Each phase corresponds to a
 * different stage of interaction or game progress. The dialogues are
 * then allocated and stored in the NPC's `dialogue` structure using
 * `allocate_dialogues`.
 *
 * The number of phases is determined automatically based on the size
 * of the `calico_kitty_dialogues` array.
 *
 * @param game Pointer to the game context (used for memory management).
 * @param npc Pointer to the NPC whose dialogue structure will be filled.
 */
void	init_calico_kitty_dialogues(t_game *game, t_npc *npc)
{
	static char	*calico_kitty_dialogues[][10] = {
	{CKD_0_0, NULL},
	{CKD_1_0, CKD_1_1, CKD_1_2, CKD_1_3, CKD_1_4,
		CKD_1_5, CKD_1_6, CKD_1_7, CKD_1_8, NULL},
	{CKD_2_0, CKD_2_1, CKD_2_2, NULL},
	{CKD_3_0, CKD_3_1, CKD_3_2, CKD_3_3, CKD_3_4, NULL},
	{CKD_4_0, CKD_4_1, CKD_4_2, CKD_4_3, CKD_4_4, CKD_4_5, NULL},
	{CKD_5_0, CKD_5_1, NULL},
	{CKD_6_0, CKD_6_1, CKD_6_2, NULL},
	{NULL}, {NULL}, {NULL}
	};

	npc->dialogue.phase_count
		= sizeof(calico_kitty_dialogues) / sizeof(calico_kitty_dialogues[0]);
	allocate_dialogues
		(game, &npc->dialogue, calico_kitty_dialogues,
			npc->dialogue.phase_count);
}

/**
 * @brief Initializes the sprite paths and sizes for the calico kitty NPC.
 *
 * This function assigns predefined animation frame paths to the `t_sprite`
 * structure of the NPC for different states: idle, moving, and speaking.
 * The number of frames for each animation is automatically calculated.
 * The sprite size is also set to a fixed resolution (64x64 pixels).
 *
 * These sprite paths are later used for texture loading and animation rendering.
 *
 * @param npc Pointer to the NPC structure whose sprite data is initialized.
 */
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

/**
 * @brief Initializes a calico kitty NPC with predefined attributes.
 *
 * This function sets the base parameters of a calico kitty NPC, including
 * its type, name, position, movement speed, pathfinding data, sprite animations,
 * and dialogue phases. The position is adjusted to center the NPC in its tile.
 *
 * It prepares the NPC for logic and rendering by calling setup functions for:
 * - pathfinding (`init_npc_pathfinding`, `generate_npc_waypoints`)
 * - sprite loading (`init_calico_kitty_sprites`, `init_npc_animation`)
 * - dialogue data (`init_calico_kitty_dialogues`)
 *
 * @param game Pointer to the game structure.
 * @param npc Pointer to the NPC structure to initialize.
 * @param pos Initial tile-based position of the NPC.
 */
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

/**
 * @brief Spawns a calico kitty NPC at the specified map coordinates.
 *
 * This function allocates memory for a new NPC of type "calico kitty",
 * initializes its attributes (position, animations, dialogues, etc.)
 * using `init_calico_kitty`, and adds it to the global NPC list.
 *
 * @param game Pointer to the main game structure.
 * @param x X-coordinate (tile-based) where the kitty should be spawned.
 * @param y Y-coordinate (tile-based) where the kitty should be spawned.
 */
void	spawn_calico_kitty(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	init_calico_kitty(game, npc, pos);
	update_npc_list(game, npc);
}
