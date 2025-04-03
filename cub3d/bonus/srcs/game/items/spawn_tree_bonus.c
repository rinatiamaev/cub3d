/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tree_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:15:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:00:15 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes a static tree item.
 *
 * Sets the type and name of the item as a tree, positions it at the center of
 * the specified tile, and loads its texture from file.
 *
 * @param game Pointer to the game context.
 * @param item Pointer to the item structure to initialize.
 * @param pos Position of the tree in world coordinates (tile-aligned).
 */
static void	init_tree(t_game *game, t_item *item, t_dpoint pos)
{
	item->type = "static";
	item->name = "tree";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, TREE_TEX, game->mlx);
}

/**
 * @brief Spawns a tree item into the game world.
 *
 * Allocates memory for a new tree item, initializes it, and registers it
 * in the global item list. The tree is positioned at the center of the tile.
 *
 * @param game Pointer to the game context.
 * @param x Tile-based x-coordinate for tree placement.
 * @param y Tile-based y-coordinate for tree placement.
 */
void	spawn_tree(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	init_tree(game, item, pos);
	update_item_list(game, item);
}
