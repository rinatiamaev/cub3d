/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc_patrol_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:29:13 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:30:42 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Updates the NPC's patrol path using A* pathfinding.
 *
 * This function calculates a new path from the NPC's current position to its
 * current patrol waypoint using the A* algorithm. The result is stored in
 * the NPC's path array.
 *
 * @param game Pointer to the game context.
 * @param npc Pointer to the NPC whose path is being updated.
 */
static void	update_npc_patrol_path(t_game *game, t_npc *npc)
{
	t_point	start;
	t_point	goal;

	start = (t_point){(int)npc->pos.x, (int)npc->pos.y};
	goal = (t_point){
		(int)npc->waypoints[npc->current_wp].x,
		(int)npc->waypoints[npc->current_wp].y};
	a_star_path(game, npc, start, goal);
}

/**
 * @brief Checks if the NPC's patrol path is valid.
 *
 * A patrol path is considered valid if it exists and contains at least
 * one point to follow.
 *
 * @param npc Pointer to the NPC whose path is being checked.
 * @return true if the path exists and is non-empty, false otherwise.
 */
static bool	is_patrol_path_valid(t_npc *npc)
{
	return (npc->path && npc->path_length > 0);
}

/**
 * @brief Advances the NPC's current waypoint and updates its patrol path.
 *
 * Increments the NPC's path index to move to the next point
 * in the current path. If the NPC has reached the end of the waypoint list,
 * new waypoints are generated. If the NPC has reached the end of the current
 * path, it cycles to the next waypoint and recalculates a new path
 * to that waypoint.
 *
 * @param game Pointer to the game context.
 * @param npc Pointer to the NPC whose patrol progression is being updated.
 */
static void	handle_waypoint_progression(t_game *game, t_npc *npc)
{
	npc->path_index++;
	if (npc->path_index == npc->waypoint_count)
		generate_npc_waypoints(npc, game);
	if (npc->path_index >= npc->path_length)
	{
		npc->path_index = 0;
		npc->path_length = 0;
		npc->current_wp = (npc->current_wp + 1) % npc->waypoint_count;
		update_npc_patrol_path(game, npc);
	}
}

/**
 * @brief Moves the NPC along its patrol path.
 *
 * This function handles NPC patrol behavior. If the current patrol path
 * is invalid, it attempts to regenerate it. If the path is still invalid
 * after regeneration, new waypoints are generated. If a valid path is
 * available, the NPC moves towards the current target in the path. When the
 * target is reached, it progresses to the next waypoint.
 *
 * @param game Pointer to the game context.
 * @param npc Pointer to the NPC being updated.
 * @param delta_time Time elapsed since the last frame (used to scale movement).
 */
void	move_npc_patrol(t_game *game, t_npc *npc, double delta_time)
{
	t_dpoint	target;

	if (!is_patrol_path_valid(npc))
	{
		update_npc_patrol_path(game, npc);
		if (!is_patrol_path_valid(npc))
		{
			generate_npc_waypoints(npc, game);
			return ;
		}
	}
	target = npc->path[npc->path_index];
	if (move_npc(game, npc, target, delta_time))
		handle_waypoint_progression(game, npc);
}
