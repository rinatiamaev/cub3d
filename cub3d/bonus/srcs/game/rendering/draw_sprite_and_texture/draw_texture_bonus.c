/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:45 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:22:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes sprite draw data from a standalone texture.
 *
 * This function wraps a raw texture in a temporary `t_sprite` structure,
 * treating it as a sprite with a single idle frame. It is used to reuse the
 * existing sprite rendering pipeline (`init_sprite_draw_data` and
 * `draw_sprite_column`) to draw non-animated elements like static objects
 * or effects (trees, buckets, etc.).
 *
 * The temporary sprite has:
 * - Position set to `texture_pos`
 * - 1 idle frame (the given texture)
 * - No animation timing or additional frames
 *
 * @param data Pointer to the sprite draw data to initialize.
 * @param player The player structure (used for view transformation).
 * @param texture The texture to draw as a sprite.
 * @param texture_pos The world-space position of the texture.
 * @return true if the texture is within view and drawable, false otherwise.
 */
static bool	init_texture_as_sprite(t_sprite_draw *data, t_player player,
									t_texture *texture, t_dpoint texture_pos)
{
	t_sprite	temp_sprite;

	temp_sprite.pos = texture_pos;
	temp_sprite.anim_start = 0;
	temp_sprite.idle_frames_count = 1;
	temp_sprite.idle_frames = texture;
	return (init_sprite_draw_data(data, player, &temp_sprite));
}

/**
 * @brief Renders a standalone texture in the world as a sprite.
 *
 * This function uses the sprite rendering pipeline to draw a texture
 * at a specific world position (`texture_pos`). It wraps the texture in
 * a temporary sprite and projects it onto the screen relative to the
 * player's viewpoint.
 *
 * The rendering follows these steps:
 * 1. Initializes a temporary sprite with one frame using the given texture.
 * 2. Computes on-screen bounds and projection data using the player's view.
 * 3. Iterates over each visible vertical stripe of the texture and renders it
 *    using `draw_sprite_column`.
 *
 * This function is ideal for rendering non-animated world objects like trees,
 * decorative elements, or effects that require depth testing.
 *
 * @param game Pointer to the game state, including player and render buffer.
 * @param texture Pointer to the texture to draw.
 * @param texture_pos World-space position where the texture should appear.
 * @param z_buffer Array of wall depths for occlusion checking.
 */
void	draw_texture(t_game *game, t_texture *texture,
										t_dpoint texture_pos, double *z_buffer)
{
	t_sprite_draw	data;

	if (!init_texture_as_sprite(&data, game->player, texture, texture_pos))
		return ;
	data.stripe_x = data.draw_start.x;
	while (data.stripe_x < data.draw_end.x)
	{
		draw_sprite_column(game, &data, z_buffer);
		data.stripe_x++;
	}
}
