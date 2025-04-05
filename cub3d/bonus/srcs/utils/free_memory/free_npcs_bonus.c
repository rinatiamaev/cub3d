/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_npcs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:30:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:54:15 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Frees an array of texture frames.
 *
 * Iterates through the given array of t_texture frames and destroys each
 * texture using MiniLibX. Then frees the array itself.
 *
 * @param game Pointer to the game instance (for mlx context).
 * @param frames Array of t_texture to be destroyed.
 * @param count Number of textures in the array.
 */
void	free_tex_frames(t_game *game, t_texture *frames, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (frames[j].ptr)
			mlx_destroy_image(game->mlx, frames[j].ptr);
		j++;
	}
	free(frames);
}

/**
 * @brief Frees all animation frames associated with an NPC sprite.
 *
 * Releases memory for idle, move, speak, and optionally hit animations
 * using `free_tex_frames`.
 *
 * @param game Pointer to the game instance (for mlx context).
 * @param sprite Pointer to the NPC's sprite structure.
 */
void	free_npc_textures(t_game *game, t_sprite *sprite)
{
	free_tex_frames(game, sprite->idle_frames, sprite->idle_frames_count);
	free_tex_frames(game, sprite->move_frames, sprite->move_frames_count);
	free_tex_frames(game, sprite->speak_frames, sprite->speak_frames_count);
	if (sprite->hit_frames)
		free_tex_frames(game, sprite->hit_frames, sprite->hit_frames_count);
}

/**
 * @brief Frees dynamically allocated NPC dialogue data.
 *
 * Frees each string array representing a phase of dialogue,
 * then frees the top-level dialogue arrays: `dialogues` and
 * `dialogue_count`.
 *
 * @param dialog Pointer to the t_dial structure.
 */
static void	free_dialogues(t_dial *dialog)
{
	int	i;

	i = 0;
	while (i < dialog->phase_count)
	{
		ft_free_array((void **)dialog->dialogues[i]);
		i++;
	}
	free(dialog->dialogues);
	free(dialog->dialogue_count);
}

/**
 * @brief Frees all resources related to a single NPC.
 *
 * Deallocates:
 * - NPC waypoints
 * - Texture animations
 * - Pathfinding data (path and A* structure)
 * - Dialogue data
 *
 * Also safely handles null pointers.
 *
 * @param game Pointer to the game context.
 * @param npc Pointer to the NPC to free.
 */
void	free_single_npc(t_game *game, t_npc *npc)
{
	if (!npc)
		return ;
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
	free_dialogues(&npc->dialogue);
	free(npc);
}

/**
 * @brief Frees all NPCs in the game.
 *
 * Iterates through the NPC array, calling `free_single_npc` on each one,
 * and then frees the NPC list.
 *
 * @param game Pointer to the game structure containing the NPC array.
 */
void	free_npcs(t_game *game)
{
	int	i;

	if (!game->npcs || game->npc_count == 0)
		return ;
	i = 0;
	while (i < game->npc_count)
	{
		free_single_npc(game, game->npcs[i]);
		i++;
	}
	free(game->npcs);
}
