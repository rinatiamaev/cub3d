/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:34:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:42:42 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Renders an NPC entity based on its type.
 *
 * This function dispatches the NPC to the appropriate draw routine based on
 * its `type` string. It supports:
 *
 * - `"kitty"` → uses `draw_kitty_npc`
 * - `"fireSpirit"` → uses `draw_fire_spirit`
 *
 * Additional NPC types can be supported by extending this function.
 *
 * @param game Pointer to the game state.
 * @param npc Pointer to the NPC entity to render.
 * @param z_buffer Z-buffer used for depth sorting.
 */
static void	draw_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	if (ft_strcmp(npc->type, "kitty") == 0)
		draw_kitty_npc(game, npc, z_buffer);
	else if (ft_strcmp(npc->type, "fireSpirit") == 0)
		draw_fire_spirit(game, npc, z_buffer);
}

/**
 * @brief Renders an item entity based on its name.
 *
 * This function selects the appropriate rendering method depending on the
 * item's name:
 *
 * - `"key"` → uses `draw_key` to render the item as a sprite.
 * - Any other item → rendered using `draw_texture`, which projects a static
 *   texture at the item's position.
 *
 * @param game Pointer to the game state.
 * @param item Pointer to the item to render.
 * @param z_buffer Z-buffer used for depth sorting.
 */
static void	draw_item(t_game *game, t_item *item, double *z_buffer)
{
	if (ft_strcmp(item->name, "key") == 0)
		draw_key(game, item, z_buffer);
	else
		draw_texture(game, &item->texture, item->pos, z_buffer);
}

/**
 * @brief Renders all active entities in the game world.
 *
 * This function iterates through the `game->entities` array and draws each
 * entity according to its type:
 *
 * - NPCs are passed to `draw_npc`
 * - Items are passed to `draw_item`
 *
 * Entity rendering uses the Z-buffer to maintain correct depth sorting
 * relative to walls and other entities.
 *
 * @param game Pointer to the game state containing all entities.
 * @param z_buffer Z-buffer used for occlusion and depth testing.
 */
void	draw_entities(t_game *game, double *z_buffer)
{
	int	i;

	i = -1;
	while (++i < game->entity_count)
	{
		if (game->entities[i].type == NPC)
			draw_npc(game, (t_npc *)game->entities[i].ptr, z_buffer);
		else if (game->entities[i].type == ITEM)
			draw_item(game, (t_item *)game->entities[i].ptr, z_buffer);
	}
}
