/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fire_spirit_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:32:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/05 19:57:43 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Retrieves the current idle frame texture for an NPC.
 *
 * This function returns the current texture frame from the NPC's idle
 * animation, based on `anim_index`. If the index is out of bounds (negative
 * or greater than the number of frames), it defaults to frame 0 to avoid
 * invalid memory access.
 *
 * @param npc Pointer to the NPC whose texture is being queried.
 * @return Pointer to the texture corresponding to the current idle frame.
 */
static inline t_texture	*get_npc_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.idle_frames_count)
		index = 0;
	return (&npc->sprite.idle_frames[index]);
}

/**
 * @brief Retrieves the current hit frame texture for an NPC.
 *
 * This function returns the texture for the NPC's current hit animation
 * frame, based on `anim_index`. If the index is out of range, it safely
 * defaults to frame 0 to prevent out-of-bounds access.
 *
 * @param npc Pointer to the NPC whose hit texture is requested.
 * @return Pointer to the texture corresponding to the current hit frame.
 */
static inline t_texture	*get_hit_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.hit_frames_count)
		index = 0;
	return (&npc->sprite.hit_frames[index]);
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
 * @brief Renders the fire spirit NPC using the appropriate texture frame.
 *
 * This function handles the drawing of the fire spirit entity based on
 * its state:
 *
 * - If the NPC is an enemy and currently in the HIT state, it uses the
 *   hit animation frame (`get_hit_texture`).
 * - Otherwise, it uses the regular idle animation frame (`get_npc_texture`).
 *
 * A temporary `t_sprite` is initialized with the selected frame, and
 * `draw_sprite` is used to project and render it on screen using the
 * player's camera and the current Z-buffer.
 *
 * @param game Pointer to the game state (for rendering and player data).
 * @param npc Pointer to the fire spirit NPC to be rendered.
 * @param z_buffer Z-buffer array used for depth testing.
 */
void	draw_fire_spirit(t_game *game, t_npc *npc, double *z_buffer)
{
	t_texture	*tex;
	t_sprite	temp;

	if (npc->is_enemy && npc->state == HIT)
		tex = get_hit_texture(npc);
	else
		tex = get_npc_texture(npc);
	setup_temp_sprite(&temp, npc, tex);
	draw_sprite(game, game->player, &temp, z_buffer);
}
