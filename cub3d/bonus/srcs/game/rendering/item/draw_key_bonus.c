/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:16:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/05 19:56:53 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Renders the key item sprite in the world.
 *
 * This function draws the key item using the standard sprite rendering
 * system. It projects the sprite relative to the player's position and
 * uses the Z-buffer for proper depth sorting.
 *
 * @param game Pointer to the game state (contains player and render data).
 * @param item Pointer to the key item (contains its sprite).
 * @param z_buffer Z-buffer used for depth testing against walls and other
 *        objects.
 */
void	draw_key(t_game *game, t_item *item, double *z_buffer)
{
	draw_sprite(game, game->player, &item->sprite, z_buffer);
}
