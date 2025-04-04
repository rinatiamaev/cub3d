/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout_helpers_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:00:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:09:14 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Validates a character in the map and updates player info if needed.
 *
 * This function checks if the character is valid within the context of the map.
 * If the character represents a player start ('N', 'S', 'E', or 'W'), it sets
 * the player position and direction, and increments the player count.
 *
 * @param game Pointer to the game context.
 * @param c The character to validate.
 * @param row The row index in the map.
 * @param col The column index in the map.
 */
void	check_map_chars(t_game *game, char c, int row, int col)
{
	if (!ft_strchr(" 012NSEWKCDFPBTIX", c))
		error(game, "Invalid character in map layout");
	if (ft_strchr("NSEW", c))
	{
		game->player.pos.x = col;
		game->player.pos.y = row;
		game->player.conf_dir = c;
		game->map->player_count++;
	}
}

/**
 * @brief Ensures that a map cell is not exposed to the outer void.
 *
 * Verifies that the given cell is not located on the edge of the map or
 * adjacent to a void (' ') space. Called only for walkable cells or player
 * start positions.
 *
 * @param game Pointer to the game context.
 * @param map Pointer to the map structure.
 * @param row Row index of the cell.
 * @param col Column index of the cell.
 */
void	check_map_boundaries(t_game *game, t_map *map, int row, int col)
{
	if (row == 0 || row == map->size.y - 1
		|| col == 0 || col == map->size.x - 1)
		error(game, "Map is not closed (cell on boundary)");
	if (map->map_layout[row - 1][col] == ' '
		|| map->map_layout[row + 1][col] == ' '
		|| (col > 0 && map->map_layout[row][col - 1] == ' ')
		|| (col + 1 < (int)ft_strlen(map->map_layout[row])
		&& map->map_layout[row][col + 1] == ' '))
		error(game, "Map is not closed (cell adjacent to void)");
}

/**
 * @brief Validates a single cell in the map layout.
 *
 * Performs character validation and checks map closure for walkable
 * and player-start positions. This function encapsulates all per-cell checks.
 *
 * @param game Pointer to the game context.
 * @param map Pointer to the map structure.
 * @param row Row index of the cell.
 * @param col Column index of the cell.
 */
void	process_map_cell(t_game *game, t_map *map, int row, int col)
{
	char	c;

	c = map->map_layout[row][col];
	check_map_chars(game, c, row, col);
	if (c == '0' || ft_strchr("NSEW", c))
		check_map_boundaries(game, map, row, col);
}

/**
 * @brief Calculates the dimensions of the map layout.
 *
 * This function determines the width and height of the map layout by
 * iterating through each row and finding the maximum length. The height
 * is simply the number of rows in the layout.
 *
 * @param game Pointer to the game context (used for error handling).
 * @param map Pointer to the map structure containing the layout.
 */
void	calculate_map_dimension(t_game *game, t_map *map)
{
	int	i;
	int	current_length;

	map->size.y = ft_arraysize((void **)map->map_layout);
	if (map->size.y == 0)
		error(game, "Map layout is empty");
	i = 0;
	while (map->map_layout[i])
	{
		current_length = ft_strlen(map->map_layout[i]);
		if (current_length > map->size.x)
			map->size.x = current_length;
		i++;
	}
}

/**
 * @brief Normalizes all map rows to the same width.
 *
 * Ensures that each map row has the same length by padding shorter rows
 * with spaces. This simplifies later map parsing and rendering.
 *
 * @param game Pointer to the game context.
 * @param map Pointer to the map structure.
 */
void	normalize_map_layout(t_game *game, t_map *map)
{
	int		row;
	int		len;
	char	*new_line;

	row = 0;
	while (row < map->size.y)
	{
		len = ft_strlen(map->map_layout[row]);
		if (len < map->size.x)
		{
			new_line = x_calloc(game, map->size.x + 1, sizeof(char));
			ft_memcpy(new_line, map->map_layout[row], len);
			while (len < map->size.x)
			{
				new_line[len] = ' ';
				len++;
			}
			free(map->map_layout[row]);
			map->map_layout[row] = new_line;
		}
		row++;
	}
}
