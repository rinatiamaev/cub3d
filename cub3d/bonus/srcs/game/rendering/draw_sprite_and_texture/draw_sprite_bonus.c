/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:05:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:16:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Renders a sprite on the screen using perspective projection.
 *
 * This function computes and draws a vertical stripe-based projection
 * of the sprite based on the player's position and camera orientation.
 * The sprite's dimensions, screen space position, and texture mapping
 * are precomputed via `init_sprite_draw_data()`. The rendering loop
 * draws each column of the sprite while respecting depth ordering
 * using the `z_buffer` to prevent overdrawing behind walls.
 *
 * @param game Pointer to the game context.
 * @param player The current state of the player (position, direction, etc).
 * @param sprite Pointer to the sprite to render.
 * @param z_buffer Array storing the perpendicular distances to walls
 *        for each screen column. Used to ensure the sprite is rendered
 *        only if it's closer than the wall at that x position.
 */
void	draw_sprite(t_game *game, t_player player, t_sprite *sprite,
															double *z_buffer)
{
	t_sprite_draw	data;

	if (!init_sprite_draw_data(&data, player, sprite))
		return ;
	data.stripe_x = data.draw_start.x;
	while (data.stripe_x < data.draw_end.x)
	{
		draw_sprite_column(game, &data, z_buffer);
		data.stripe_x++;
	}
}
