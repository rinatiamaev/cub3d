/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_move_valid.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:44:16 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/22 17:19:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if a position is too close to any NPC.
 *
 * Prevents the player from moving into a position that is too close
 * to a non-player character (NPC). Uses cab (Manhattan) distance
 * for the proximity check.
 *
 * @param game Pointer to the game structure.
 * @param next_pos The position to check for proximity to NPCs.
 * @return true if too close to an NPC, false otherwise.
 */
static bool	is_position_near_npc(t_game *game, t_dpoint next_pos)
{
	t_npc	*npc;
	double	npc_distance;
	double	minimum_distance;
	int		i;

	i = 0;
	minimum_distance = 0.3;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		npc_distance = ft_cab_dist_dpoint(next_pos, npc->pos);
		if (npc_distance < minimum_distance)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Checks if a position is too close to any item.
 *
 * Prevents the player from moving into a position that is too close to
 * an item. Uses cab (Manhattan) distance for the proximity check.
 *
 * @param game Pointer to the game structure.
 * @param next_pos The position to check for proximity to items.
 * @return true if too close to an item, false otherwise.
 */
static bool	is_position_near_item(t_game *game, t_dpoint next_pos)
{
	t_item	*item;
	double	item_distance;
	double	minimum_distance;
	int		i;

	i = 0;
	minimum_distance = 0.6;
	while (i < game->item_count)
	{
		item = game->items[i];
		item_distance = ft_cab_dist_dpoint(next_pos, item->pos);
		if (item_distance < minimum_distance)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Checks if the player can walk through a door at the given grid pos.
 *
 * If there is no door at the position, the function returns true.
 * If a door exists, it must be in the open state to be walkable.
 *
 * @param game Pointer to the game structure.
 * @param grid_pos The grid position to check for a door.
 * @return true if walkable, false if blocked by a closed or locked door.
 */
static bool	is_door_walkable_player(t_game *game, t_point grid_pos)
{
	t_door	*door;

	door = find_door_at(game, grid_pos);
	if (!door)
		return (true);
	return (door->state == DOOR_OPEN);
}

/**
 * @brief Checks if the player's next position is valid for movement.
 *
 * A position is valid if:
 * - it is within the map bounds,
 * - it does not collide with an NPC,
 * - it does not collide with an item,
 * - it is not blocked by a closed or locked door.
 *
 * @param game Pointer to the game structure.
 * @param next_pos The next position the player wants to move to.
 * @return true if the move is allowed, false otherwise.
 */
bool	is_player_move_valid(t_game *game, t_dpoint next_pos)
{
	t_point	grid_pos;

	grid_pos = (t_point){(int)next_pos.x, (int)next_pos.y};
	if (!is_map_position_valid_player(game, next_pos))
		return (false);
	if (is_position_near_npc(game, next_pos))
		return (false);
	if (is_position_near_item(game, next_pos))
		return (false);
	if (!is_door_walkable_player(game, grid_pos))
		return (false);
	return (true);
}
