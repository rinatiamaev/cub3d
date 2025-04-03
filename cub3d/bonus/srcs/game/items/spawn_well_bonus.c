/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_well_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:00:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes a static well item.
 *
 * Sets the item's type and name to represent a well, positions it at the
 * center of the specified tile, and loads its associated texture.
 *
 * @param game Pointer to the game context.
 * @param item Pointer to the item structure to initialize.
 * @param pos Position of the well in world coordinates (tile-aligned).
 */
static void	init_well(t_game *game, t_item *item, t_dpoint pos)
{
	item->type = "static";
	item->name = "well";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, WELL_TEX, game->mlx);
}

/**
 * @brief Spawns a well item into the game world.
 *
 * Allocates and initializes a new well item, then adds it to the game's
 * item list. The well is placed at the center of the given tile coordinates.
 *
 * @param game Pointer to the game context.
 * @param x Tile-based x-coordinate for the well.
 * @param y Tile-based y-coordinate for the well.
 */
void	spawn_well(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	init_well(game, item, pos);
	update_item_list(game, item);
}
