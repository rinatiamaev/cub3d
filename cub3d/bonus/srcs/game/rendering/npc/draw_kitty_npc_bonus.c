/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kitty_npc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:03:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:38:27 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Retrieves the current movement frame texture for an NPC.
 *
 * This function selects the appropriate walking animation frame for the NPC
 * based on its movement direction relative to the player. It:
 *
 * 1. Determines the movement block (direction) using `get_walk_block`.
 * 2. Computes the base animation index for that direction.
 * 3. Adds the current animation index (modulo 4) to get the frame offset.
 * 4. Clamps the index to ensure it's within bounds.
 *
 * This allows for directional walking animations (e.g., walk_left,
 * walk_right) with frame cycling per direction.
 *
 * @param game Pointer to the game state (used to access player position).
 * @param npc Pointer to the NPC whose movement frame is being queried.
 * @return Pointer to the texture for the current movement animation frame.
 */
static inline t_texture	*get_npc_movement_texture(t_game *game, t_npc *npc)
{
	int	block;
	int	base_index;
	int	index;

	block = get_walk_block(npc, &game->player);
	base_index = get_walk_animation_base_index(block);
	index = base_index + (npc->sprite.anim_index % 4);
	if (index < 0 || index >= npc->sprite.move_frames_count)
		index = base_index;
	return (&npc->sprite.move_frames[index]);
}

/**
 * @brief Retrieves the current idle (waiting) frame texture for an NPC.
 *
 * This function returns the texture corresponding to the current frame of
 * the NPC's idle animation (used when the NPC is in the WAIT state).
 * If the animation index is out of bounds, it defaults to frame 0 to
 * avoid invalid access.
 *
 * @param npc Pointer to the NPC whose idle texture is being queried.
 * @return Pointer to the texture for the current idle frame.
 */
static inline t_texture	*get_npc_wait_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.idle_frames_count)
		index = 0;
	return (&npc->sprite.idle_frames[index]);
}

/**
 * @brief Retrieves the current speaking frame texture for an NPC.
 *
 * This function returns the texture corresponding to the current animation
 * frame in the NPC's speaking animation sequence. If the `anim_index` is
 * out of bounds, it safely defaults to frame 0.
 *
 * This is typically used when the NPC is in the SPEAK state and needs to
 * render a talking animation.
 *
 * @param npc Pointer to the NPC.
 * @return Pointer to the texture for the current speaking frame.
 */
static inline t_texture	*get_npc_speak_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.speak_frames_count)
		index = 0;
	return (&npc->sprite.speak_frames[index]);
}

/**
 * @brief Initializes a temporary sprite structure for NPC rendering.
 *
 * This function sets up a minimal `t_sprite` instance using a single
 * texture frame. It copies the NPC's position and size, sets the frame
 * count to 1, and assigns the provided texture as the only idle frame.
 *
 * This is used to reuse the sprite rendering system (`draw_sprite`) for
 * both animated and non-animated rendering without modifying the original
 * NPC sprite structure.
 *
 * @param temp Pointer to the temporary sprite structure to initialize.
 * @param npc Pointer to the NPC providing position and size.
 * @param tex Pointer to the texture frame to assign as the idle frame.
 */
static inline void	setup_temp_sprite(t_sprite *temp, t_npc *npc,
														t_texture *tex)
{
	ft_memset(temp, 0, sizeof(t_sprite));
	temp->pos = npc->pos;
	temp->size = npc->sprite.size;
	temp->idle_frames_count = 1;
	temp->idle_frames = tex;
}

/**
 * @brief Renders a kitty-type NPC using the appropriate animation frame.
 *
 * This function selects the correct texture frame for the kitty NPC based
 * on its current state, wraps it into a temporary sprite, and renders it
 * using the sprite projection system. The states are handled as follows:
 *
 * - `WAIT`: Uses an idle (waiting) frame.
 * - `PATROL` / `FOLLOW`: Uses a directional movement frame based on
 *   movement relative to the player.
 * - `SPEAK`: Uses a speaking animation frame.
 *
 * The texture is rendered using `draw_sprite`, which applies depth sorting
 * and perspective projection.
 *
 * @param game Pointer to the game state (includes player and rendering data).
 * @param npc Pointer to the kitty NPC to be rendered.
 * @param z_buffer Z-buffer used for occlusion testing during sprite rendering.
 */
void	draw_kitty_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	t_texture	*tex;
	t_sprite	temp;

	tex = NULL;
	if (npc->state == WAIT)
		tex = get_npc_wait_texture(npc);
	else if (npc->state == PATROL)
		tex = get_npc_movement_texture(game, npc);
	else if (npc->state == FOLLOW)
		tex = get_npc_movement_texture(game, npc);
	else if (npc->state == SPEAK)
		tex = get_npc_speak_texture(npc);
	setup_temp_sprite(&temp, npc, tex);
	draw_sprite(game, game->player, &temp, z_buffer);
}
