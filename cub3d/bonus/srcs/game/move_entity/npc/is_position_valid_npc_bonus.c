/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_position_valid_npc_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:07:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:21:09 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if an NPC is allowed to walk through a door at a given pos.
 *
 * This function determines whether an NPC can move through a door located at
 * the specified grid position. It always allows passage if there is no door,
 * and conditionally allows it if the NPC is in the FOLLOW state.
 *
 * @param game Pointer to the game context.
 * @param npc Pointer to the NPC.
 * @param pos Grid position to check (usually the next cell).
 * @return true if the door is walkable for this NPC, false otherwise.
 */
static bool	is_door_walkable_npc(t_game *game, t_npc *npc, t_point pos)
{
	t_door	*door;

	door = find_door_at(game, pos);
	if (!door)
		return (true);
	if (npc->state == FOLLOW)
		return (true);
	return (false);
}

/**
 * @brief Checks if the given position is occupied by any NPC.
 *
 * This function iterates through all NPCs in the game and checks if
 * any of them occupy the specified position.
 *
 * @param game Pointer to the game structure.
 * @param pos The position to check for NPC occupation.
 * @return true if occupied by any NPC, false otherwise.
 */
static bool	is_occupied_by_any_npc(t_game *game, t_point pos)
{
	int	i;

	i = 0;
	while (i < game->npc_count)
	{
		if ((int)game->npcs[i]->pos.x == pos.x
			&& (int)game->npcs[i]->pos.y == pos.y)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Checks if an NPC can walk on a given map position.
 *
 * This function verifies whether a map pos is valid for an NPC to move to.
 * The position is considered invalid if it is a wall or if it lies outside the
 * boundaries of the map.
 *
 * @param game Pointer to the game context.
 * @param pos Position in floating point coordinates (x, y).
 * @return true if the position is valid for the NPC, false otherwise.
 */
static bool	is_map_position_valid_npc(t_game *game, t_dpoint pos)
{
	t_point			grid_pos;

	grid_pos = (t_point){(int)pos.x, (int)pos.y};
	if (is_wall(game, grid_pos))
		return (false);
	if (!is_within_bounds(game, grid_pos))
		return (false);
	return (true);
}

/**
 * @brief Checks whether an NPC can move to a specific grid position.
 *
 * This function performs a comprehensive validation to determine if an NPC
 * can move to the given map tile. It verifies that:
 * - The position is within bounds and not a wall.
 * - The position is not already in the A* algorithm's open list (if provided).
 * - The position is not currently occupied by another NPC.
 * - The position is not blocked by a door (unless the NPC is in FOLLOW state).
 *
 * @param game Pointer to the game context.
 * @param npc Pointer to the NPC being evaluated.
 * @param astar Pointer to the A* pathfinding data (can be NULL).
 * @param pos Grid position to validate (integer coordinates).
 * @return true if the position is valid and accessible for the NPC.
 * @return false if any of the checks fail.
 */
bool	is_position_valid_npc(t_game *game, t_npc *npc, t_astar *astar,
																t_point pos)
{
	if (!is_map_position_valid_npc(game,
			(t_dpoint){(double)pos.x, (double)pos.y}))
		return (false);
	if (astar && astar->open_list[pos.y][pos.x])
		return (false);
	if (is_occupied_by_any_npc(game, pos))
		return (false);
	if (!is_door_walkable_npc(game, npc, pos))
		return (false);
	return (true);
}
