/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:08:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:57:10 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Calculates the time elapsed since the last frame in seconds.
 *
 * This function uses `gettimeofday` to measure the current time and computes
 * the difference from the last time it was called. The result is the delta
 * time, used to make movement and animations frame rate-independent.
 *
 * The first time this function is called, it initializes the time reference.
 *
 * @return Elapsed time in seconds since the last call to this function.
 */

double	get_delta_time(void)
{
	struct timeval	tv;
	double			current_time;
	static double	last_time;
	double			delta_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	if (last_time == 0.0)
		last_time = current_time;
	delta_time = current_time - last_time;
	last_time = current_time;
	return (delta_time);
}

/**
 * @brief Finds a door located at a specific map position.
 *
 * Iterates through all doors in the game to find one that exactly matches
 * the given map grid position. This is commonly used to identify if a door
 * is present where the player or an NPC is interacting.
 *
 * @param game Pointer to the game state containing the list of doors.
 * @param pos Map grid position to check (in tile coordinates).
 * @return Pointer to the door at the specified position,
 *         or NULL if none found.
 */
t_door	*find_door_at(t_game *game, t_point pos)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i]->pos.x == pos.x
			&& game->doors[i]->pos.y == pos.y)
			return (game->doors[i]);
		i++;
	}
	return (NULL);
}

/**
 * @brief Checks if a map position is within the map boundaries.
 *
 * Ensures that the given (x, y) tile position lies within the valid range
 * of the map's dimensions. This is useful for preventing out-of-bounds
 * access during pathfinding, movement, or raycasting.
 *
 * @param game Pointer to the game state containing the map size.
 * @param pos Position to check (in map tile coordinates).
 * @return true if the position is inside the map, false otherwise.
 */
bool	is_within_bounds(t_game *game, t_point pos)
{
	return (pos.x >= 0 && pos.x < game->map->size.x
		&& pos.y >= 0 && pos.y < game->map->size.y);
}

/**
 * @brief Checks if a given map position corresponds to a wall tile.
 *
 * Looks up the integer value in the map matrix at the specified position
 * and compares it to the `WALL` constant. This function assumes the position
 * is already within valid map bounds.
 *
 * @param game Pointer to the game state containing the map matrix.
 * @param pos Tile position to check.
 * @return true if the tile is a wall, false otherwise.
 */
bool	is_wall(t_game *game, t_point pos)
{
	return (game->map->matrix[(int)(pos.y)][(int)pos.x] == WALL);
}

/**
 * @brief Handles game state transitions such as win or game over.
 *
 * Based on the current `game->state`, this function displays the appropriate
 * message (win or lose), and stops further game logic by returning 0.
 *
 * If the game is not in the `RUNNING` state (e.g., paused), it also returns 0.
 * Otherwise, it returns 1 to allow the main loop to continue processing.
 *
 * @param game Pointer to the game state.
 * @return 1 if the game is running and should continue, 0 otherwise.
 */
int	handle_game_state(t_game *game)
{
	if (game->state == GAME_OVER)
	{
		draw_lose_message(game);
		return (0);
	}
	else if (game->state == WIN)
	{
		draw_win_message(game);
		return (0);
	}
	else if (game->state != RUNNING)
		return (0);
	return (1);
}
