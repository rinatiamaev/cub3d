/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_line_of_sight_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:50:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:37:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes line-of-sight (LOS) ray parameters.
 *
 * Prepares the DDA algorithm by computing the ray direction vector and
 * converting the source position to map grid coordinates.
 *
 * It also computes `delta_dist`, the length the ray must travel to cross
 * the next vertical or horizontal grid line, used in step calculation.
 * If a direction component is zero, its delta is set to a large constant
 * (`INFINITY_DIST`) to avoid division by zero.
 *
 * @param los Pointer to the line-of-sight data structure to initialize.
 * @param src World-space starting point (e.g. NPC or player position).
 * @param target World-space end point (e.g. line-of-sight target).
 */
static void	init_los_data(t_los *los, t_dpoint src, t_dpoint target)
{
	los->ray_dir.x = target.x - src.x;
	los->ray_dir.y = target.y - src.y;
	los->map_check.x = (int)floor(src.x);
	los->map_check.y = (int)floor(src.y);
	if (los->ray_dir.x != 0)
		los->delta_dist.x = fabs(1.0 / los->ray_dir.x);
	else
		los->delta_dist.x = INFINITY_DIST;
	if (los->ray_dir.y != 0)
		los->delta_dist.y = fabs(1.0 / los->ray_dir.y);
	else
		los->delta_dist.y = INFINITY_DIST;
}

/**
 * @brief Calculates DDA stepping direction and initial side distances.
 *
 * This function determines the direction in which the ray should step
 * on both the x and y axes (`step`) based on the sign of the ray direction.
 *
 * It also computes the initial distance from the ray origin to the first
 * vertical or horizontal side it will cross (`side_dist`). These values
 * are necessary to begin the DDA grid traversal.
 *
 * @param los Pointer to the line-of-sight data structure to populate.
 * @param src World-space starting position of the ray.
 */
static void	calculate_step_and_side_dist(t_los *los, t_dpoint src)
{
	if (los->ray_dir.x < 0)
	{
		los->step.x = -1;
		los->side_dist.x
			= (src.x - los->map_check.x) * los->delta_dist.x;
	}
	else
	{
		los->step.x = 1;
		los->side_dist.x
			= (los->map_check.x + 1.0 - src.x) * los->delta_dist.x;
	}
	if (los->ray_dir.y < 0)
	{
		los->step.y = -1;
		los->side_dist.y
			= (src.y - los->map_check.y) * los->delta_dist.y;
	}
	else
	{
		los->step.y = 1;
		los->side_dist.y
			= (los->map_check.y + 1.0 - src.y) * los->delta_dist.y;
	}
}

/**
 * @brief Performs DDA traversal to determine line-of-sight visibility.
 *
 * This function steps through the map grid using the DDA (Digital Differential
 * Analyzer) algorithm, simulating a ray from source to target. It checks each
 * cell it enters:
 * - If the ray exits the map bounds, line of sight is blocked.
 * - If it hits a wall or door, line of sight is blocked.
 * - If it reaches the target cell, line of sight is confirmed.
 *
 * The ray advances toward the target one step at a time along either the
 * x or y axis, depending on which side distance is smaller.
 *
 * @param game Pointer to the game state (provides access to the map).
 * @param los Pointer to initialized line-of-sight data.
 * @param target The target world-space point (e.g. NPC or player).
 * @return true if line of sight is clear, false if blocked.
 */
static bool	perform_los_dda(t_game *game, t_los *los, t_dpoint target)
{
	int	cell;

	while (true)
	{
		if (los->side_dist.x < los->side_dist.y)
		{
			los->side_dist.x += los->delta_dist.x;
			los->map_check.x += los->step.x;
		}
		else
		{
			los->side_dist.y += los->delta_dist.y;
			los->map_check.y += los->step.y;
		}
		if (los->map_check.x < 0 || los->map_check.x >= game->map->size.x
			|| los->map_check.y < 0 || los->map_check.y >= game->map->size.y)
			return (false);
		cell = game->map->matrix[los->map_check.y][los->map_check.x];
		if (cell == WALL || cell == DOOR)
			return (false);
		if (los->map_check.x == (int)floor(target.x)
			&& los->map_check.y == (int)floor(target.y))
			return (true);
	}
}

/**
 * @brief Determines if there is line of sight between two points.
 *
 * This function checks whether a straight line from `src` to `target`
 * is unobstructed by walls or doors using a grid-based DDA algorithm.
 *
 * It initializes all necessary raycasting parameters and performs
 * the traversal of the map grid to test for collisions along the path.
 *
 * Commonly used for NPC vision checks or trigger-based interactions.
 *
 * @param game Pointer to the game state (provides map data).
 * @param src The starting world-space position (e.g., NPC or player).
 * @param target The target world-space position to check visibility toward.
 * @return true if there is a clear line of sight, false if obstructed.
 */
bool	has_line_of_sight(t_game *game, t_dpoint src, t_dpoint target)
{
	t_los	los;

	init_los_data(&los, src, target);
	calculate_step_and_side_dist(&los, src);
	return (perform_los_dda(game, &los, target));
}
