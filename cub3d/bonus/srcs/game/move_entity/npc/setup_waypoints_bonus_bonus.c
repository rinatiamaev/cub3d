/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_waypoints_bonus_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:04:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:27:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if a patrol point is valid.
 *
 * This function verifies that the given position is within the map bounds
 * and corresponds to a FREE_SPACE cell in the map matrix.
 *
 * @param game Pointer to the main game structure.
 * @param pos  Position to test as a patrol point.
 * @return true if the position is valid, false otherwise.
 */
static bool	is_patrol_point_valid(t_game *game, t_dpoint pos)
{
	t_point	check_pos;
	int		cell;

	check_pos = (t_point){(int)pos.x, (int)pos.y};
	if (!is_within_bounds(game, check_pos))
		return (false);
	cell = game->map->matrix[check_pos.y][check_pos.x];
	if (cell != FREE_SPACE)
		return (false);
	return (true);
}

/**
 * @brief Checks if a patrol point is sufficiently distant from others.
 *
 * Ensures that the given patrol point is at least a certain minimum
 * distance away from previously generated waypoints. This avoids clustering
 * patrol points too close to one another.
 *
 * @param npc			Pointer to the NPC structure.
 * @param count			Number of existing waypoints to compare with.
 * @param patrol_point	The candidate patrol point to validate.
 * @return true if the point is unique enough, false otherwise.
 */
static bool	is_patrol_point_unique(t_npc *npc, int count,
											t_dpoint patrol_point)
{
	int		i;
	double	minimum_distance;
	double	distance_between_points;

	i = 0;
	minimum_distance = 1.0;
	while (i < count)
	{
		distance_between_points
			= ft_cab_dist_dpoint(npc->waypoints[i], patrol_point);
		if (distance_between_points < minimum_distance)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Generates a random patrol point near the NPC's current position.
 *
 * Creates a new patrol point within a given range by applying a random
 * offset to the NPC's position. The offset is randomly selected in both
 * the X and Y directions.
 *
 * @param npc_pos	The NPC's current position.
 * @param range		The maximum offset in both X and Y directions.
 * @return A new patrol point near the NPC's position.
 */
static t_dpoint	generate_point(t_dpoint npc_pos, int range)
{
	t_point		offset;
	t_dpoint	patrol_point;

	offset.x = ft_rand(-range, range);
	offset.y = ft_rand(-range, range);
	patrol_point.x = npc_pos.x + offset.x;
	patrol_point.y = npc_pos.y + offset.y;
	return (patrol_point);
}

/**
 * @brief Allocates memory for an NPC's patrol waypoints.
 *
 * Frees any existing waypoint array and allocates a new one based on the
 * NPC's waypoint count. If the NPC or the count is invalid, the function
 * exits early.
 *
 * @param npc	Pointer to the NPC structure.
 * @param game	Pointer to the main game structure (for memory management).
 */
static void	allocate_npc_waypoints(t_npc *npc, t_game *game)
{
	if (!npc || npc->waypoint_count <= 0)
		return ;
	if (npc->waypoints)
	{
		free(npc->waypoints);
		npc->waypoints = NULL;
	}
	npc->waypoints = x_calloc(game, npc->waypoint_count, sizeof(t_dpoint));
}

/**
 * @brief Generates random patrol waypoints for the given NPC.
 *
 * Attempts to generate a set of unique and valid patrol points within the
 * specified patrol range around the NPC. If a valid point is found, it is
 * added to the NPC's waypoint list. If too many invalid points are generated
 * in a row, the function stops early.
 *
 * @param npc   Pointer to the NPC to assign waypoints to.
 * @param game  Pointer to the main game structure (used for validation and
 *              memory allocation).
 */
void	generate_npc_waypoints(t_npc *npc, t_game *game)
{
	int			waypoint_index;
	int			max_attempts;
	int			failed_attempts;
	t_dpoint	patrol_point;

	allocate_npc_waypoints(npc, game);
	waypoint_index = 0;
	max_attempts = 1000;
	failed_attempts = 0;
	while (waypoint_index < npc->waypoint_count
		&& failed_attempts < max_attempts)
	{
		patrol_point = generate_point(npc->pos, npc->patrol_range);
		if (is_patrol_point_valid(game, patrol_point)
			&& is_patrol_point_unique(npc, waypoint_index, patrol_point))
		{
			npc->waypoints[waypoint_index] = patrol_point;
			waypoint_index++;
			failed_attempts = 0;
		}
		else
			failed_attempts++;
	}
}
