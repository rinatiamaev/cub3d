/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entities_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:38:38 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:40:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Sorts entities by distance to the player in descending order.
 *
 * This function uses a simple bubble sort to reorder entities so that those
 * farther from the player come first. This is used to ensure proper rendering
 * order when drawing transparent or overlapping elements (e.g., sprites).
 *
 * Distance is calculated using the cab distance (`ft_cab_dist_dpoint`), which
 * approximates depth sorting without expensive square root operations.
 *
 * @param entities Array of entities to sort.
 * @param count Number of entities in the array.
 * @param player Pointer to the player used as distance reference.
 */
static void	sort_entities(t_entity *entities, int count, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (ft_cab_dist_dpoint(entities[j].pos, player->pos)
				< ft_cab_dist_dpoint(entities[j + 1].pos, player->pos))
				ft_swap(&entities[j], &entities[j + 1], sizeof(t_entity));
		}
	}
}

/**
 * @brief Updates and sorts the list of active game entities.
 *
 * This function refreshes the `game->entities` array by collecting all current
 * NPCs and items. It fills the array with their positions and pointers,
 * tagging them by type (`NPC` or `ITEM`). Once populated, the entities are
 * sorted by distance to the player using `sort_entities`.
 *
 * This sorted list is used during rendering to ensure correct visual layering
 * (for sprites appearing in front of or behind one another).
 *
 * @param game Pointer to the game state containing NPCs, items, and player.
 */
void	update_entities_sort(t_game *game)
{
	int	i;

	if (game->entities)
		free(game->entities);
	game->entity_count = game->npc_count + game->item_count;
	game->entities = x_calloc(game, game->entity_count, sizeof(t_entity));
	i = -1;
	while (++i < game->npc_count)
	{
		game->entities[i].type = NPC;
		game->entities[i].pos = game->npcs[i]->pos;
		game->entities[i].ptr = game->npcs[i];
	}
	i = -1;
	while (++i < game->item_count)
	{
		game->entities[game->npc_count + i].type = ITEM;
		game->entities[game->npc_count + i].pos = game->items[i]->pos;
		game->entities[game->npc_count + i].ptr = game->items[i];
	}
	sort_entities(game->entities, game->entity_count, &game->player);
}
