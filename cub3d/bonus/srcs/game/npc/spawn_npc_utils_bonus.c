/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_npc_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:26:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:42:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Sets the size of each frame in a texture animation sequence.
 *
 * This function assigns the same dimensions to all frames in a given array
 * of textures. It's used to ensure consistency between all the animation frames
 * of a sprite (e.g., idle, move, speak animations).
 *
 * @param frames Array of texture frames to update.
 * @param count Number of frames in the array.
 * @param size The size to assign to each frame (width and height).
 */
void	set_frame_sizes(t_texture *frames, int count, t_point size)
{
	int	i;

	if (!frames)
		return ;
	i = 0;
	while (i < count)
		frames[i++].size = size;
}

/**
 * @brief Initializes the animation frames for an NPC's sprite.
 *
 * This function loads all the animation frames for an NPC sprite,
 * including idle, move, speak, and optionally hit animations.
 * It then sets the uniform frame size for each animation type and 
 * initializes the starting animation timestamp using `gettimeofday()`.
 *
 * @param game Pointer to the main game structure, used for memory allocation.
 * @param sprite Pointer to the sprite structure to initialize.
 */
void	init_npc_animation(t_game *game, t_sprite *sprite)
{
	struct timeval	tv;

	load_sprite_frames_npc(game, sprite);
	set_frame_sizes
		(sprite->idle_frames, sprite->idle_frames_count, sprite->size);
	set_frame_sizes
		(sprite->move_frames, sprite->move_frames_count, sprite->size);
	set_frame_sizes
		(sprite->speak_frames, sprite->speak_frames_count, sprite->size);
	if (sprite->hit_frames)
		set_frame_sizes
			(sprite->hit_frames, sprite->hit_frames_count, sprite->size);
	gettimeofday(&tv, NULL);
	sprite->anim_start = tv.tv_sec * 1000000L + tv.tv_usec;
}

/**
 * @brief Adds a new NPC to the game's NPC list.
 *
 * This function dynamically resizes the NPC array to accommodate a new
 * NPC pointer. It uses `x_realloc` for safe reallocation, appends the
 * new NPC to the end of the list, and increments the NPC count.
 *
 * @param game Pointer to the game structure containing the NPC list.
 * @param npc Pointer to the NPC to be added.
 */
void	update_npc_list(t_game *game, t_npc *npc)
{
	game->npcs = x_realloc(game, game->npcs,
			game->npc_count * sizeof(t_npc *),
			(game->npc_count + 1) * sizeof(t_npc *));
	game->npcs[game->npc_count] = npc;
	game->npc_count++;
}

/**
 * @brief Allocates and copies dialogue lines into the NPC dialogue structure.
 *
 * This function dynamically allocates memory for a dialogue system that
 * supports multiple dialogue phases. Each phase can contain several dialogue
 * lines (strings), and each line is duplicated using `x_strdup`.
 *
 * It fills the `dialog->dialogues` 2D array with copies of the input strings
 * and stores the count of lines per phase in `dialog->dialogue_count`.
 *
 * @param game Pointer to the game structure (used for custom memory allocation).
 * @param dialog Pointer to the dialogue structure to populate.
 * @param dialogues 2D array of dialogue strings, organized by phase and line.
 * @param phase_count Total number of dialogue phases.
 */
void	allocate_dialogues(t_game *game, t_dial *dialog, char *dialogues[][10],
															int phase_count)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	dialog->dialogues = x_malloc(game, phase_count * sizeof(char **));
	dialog->dialogue_count = x_malloc(game, phase_count * sizeof(int));
	while (i < phase_count)
	{
		count = 0;
		while (dialogues[i][count])
			count++;
		dialog->dialogues[i] = x_malloc(game, (count + 1) * sizeof(char *));
		if (!dialog->dialogues[i])
			return ;
		dialog->dialogue_count[i] = count;
		j = 0;
		while (j < count)
		{
			dialog->dialogues[i][j] = x_strdup(game, dialogues[i][j]);
			j++;
		}
		dialog->dialogues[i][count] = NULL;
		i++;
	}
}

/**
 * @brief Initializes basic pathfinding parameters for the NPC.
 *
 * This function sets up default pathfinding data for an NPC, including its
 * patrol range, number of waypoints, distance threshold to switch waypoints,
 * and directional vectors used for A* pathfinding.
 *
 * It allocates and initializes an `t_astar` structure with the four cardinal
 * movement directions.
 *
 * @param game Pointer to the main game structure (used for memory allocation).
 * @param npc Pointer to the NPC to initialize pathfinding for.
 */
void	init_npc_pathfinding(t_game *game, t_npc *npc)
{
	npc->patrol_range = 10;
	npc->waypoint_count = 4;
	npc->current_wp = 1;
	npc->threshold_dist = 0.1;
	npc->astar = x_calloc(game, 1, sizeof(t_astar));
	npc->astar->direction[0] = (t_point){0, -1};
	npc->astar->direction[1] = (t_point){0, 1};
	npc->astar->direction[2] = (t_point){-1, 0};
	npc->astar->direction[3] = (t_point){1, 0};
}
