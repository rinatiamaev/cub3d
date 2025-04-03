/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bucket_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:00:12 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 09:58:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes the properties and texture of a bucket item.
 *
 * Sets the type, name, and position of the bucket, marks it as collectible,
 * and loads its texture from the defined path.
 *
 * @param game Pointer to the game context.
 * @param item Pointer to the item structure to initialize.
 * @param pos Position (tile coordinates) where the bucket will be placed.
 */
static void	init_bucket(t_game *game, t_item *item, t_dpoint pos)
{
	item->type = "static";
	item->name = "bucket";
	item->is_collectible = true;
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, BUCKET_TEX, game->mlx);
}

/**
 * @brief Spawns a new bucket item into the game world.
 *
 * Allocates memory for a new item, initializes it as a bucket, and adds it
 * to the game's list of items.
 *
 * @param game Pointer to the game context.
 * @param x X-coordinate (tile-based) for the bucket spawn location.
 * @param y Y-coordinate (tile-based) for the bucket spawn location.
 */
void	spawn_bucket(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	init_bucket(game, item, pos);
	update_item_list(game, item);
}
