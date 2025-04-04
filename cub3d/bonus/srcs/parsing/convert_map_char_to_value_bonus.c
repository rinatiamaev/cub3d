/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_char_to_value_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:39:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:07:41 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Spawns a game entity at the specified position based on map symbol.
 *
 * This function interprets the character value found in the map and calls the
 * appropriate spawn function (NPCs, items, or doors). Each entity is placed at
 * the given (x, y) coordinates.
 *
 * @param game Pointer to the game context.
 * @param cell The character from the map defining the entity type.
 * @param x X-coordinate on the map.
 * @param y Y-coordinate on the map.
 */
static void	spawn_entity_at_position(t_game *game, char cell,
															double x, double y)
{
	if (cell == 'K')
		spawn_witch_kitty(game, x, y);
	else if (cell == 'C')
		spawn_calico_kitty(game, x, y);
	else if (cell == 'D')
		spawn_door(game, x, y);
	else if (cell == 'F')
		spawn_fire_spirit(game, x, y);
	else if (cell == 'P')
		spawn_well(game, x, y);
	else if (cell == 'B')
		spawn_bucket(game, x, y);
	else if (cell == 'T')
		spawn_tree(game, x, y);
	else if (cell == 'I')
		spawn_key(game, x, y);
	else if (cell == 'X')
		spawn_exit_door(game, x, y);
}

/**
 * @brief Converts a map character representing an entity into an int value.
 *
 * This function returns a constant representing the type of the entity or tile.
 * The result is used for building the integer map matrix used in logic.
 *
 * @param cell The character symbol from the map layout.
 * @return The corresponding map integer value.
 */
static int	get_entity_map_value(char cell)
{
	if (cell == 'K' || cell == 'C' || cell == 'F'
		|| cell == 'T' || cell == 'I')
		return (FREE_SPACE);
	if (cell == 'D')
		return (DOOR);
	if (cell == 'X')
		return (EXIT_DOOR);
	if (cell == 'P')
		return (WELL);
	if (cell == 'B')
		return (BUCKET);
	return (EMPTY);
}

/**
 * @brief Spawns the entity and returns the associated map value.
 *
 * This function combines spawning logic with value conversion. It ensures that
 * the visual/spatial entity is placed in-game while also returning a numeric
 * value for matrix construction.
 *
 * @param game Pointer to the game context.
 * @param cell Map character indicating which entity to spawn.
 * @param x Column index in the map.
 * @param y Row index in the map.
 * @return Integer value representing the entity type.
 */
static int	spawn_entity(t_game *game, char cell, int x, int y)
{
	spawn_entity_at_position(game, cell, (double)x, (double)y);
	return (get_entity_map_value(cell));
}

/**
 * @brief Converts a map character to its corresponding matrix value.
 *
 * This function handles walls, player directions, empty space, and entities.
 * It determines what kind of tile or object is defined and delegates spawning
 * if needed. The result is stored in the map's integer matrix.
 *
 * @param game Pointer to the game context.
 * @param map Pointer to the map structure.
 * @param i Row index of the map.
 * @param j Column index of the map.
 * @return Integer value used for the internal matrix.
 */
int	convert_map_char_to_value(t_game *game, t_map *map, int i, int j)
{
	char	cell;

	cell = map->map_layout[i][j];
	if (cell == '1')
		return (WALL);
	else if (ft_strchr("NSEW", cell))
		return (CONF_DIR);
	else if (cell == '0')
		return (FREE_SPACE);
	else
		return (spawn_entity(game, cell, j, i));
}
