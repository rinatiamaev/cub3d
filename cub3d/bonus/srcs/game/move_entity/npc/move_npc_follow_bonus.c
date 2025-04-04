/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc_follow_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:57:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:22:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Updates the path for an NPC to follow the player using A* algorithm.
 *
 * This function sets the NPC's path from its current position to the player's
 * last known position using the A* pathfinding algorithm. The computed path is
 * stored in the NPC's internal path buffer.
 *
 * @param game Pointer to the game context.
 * @param player Pointer to the player (used to get last position).
 * @param npc Pointer to the NPC whose path is being updated.
 */
void	update_npc_follow_path(t_game *game, t_player *player, t_npc *npc)
{
	t_point	start;
	t_point	goal;

	start = (t_point){(int)npc->pos.x, (int)npc->pos.y};
	goal = (t_point){(int)player->last_pos.x, (int)player->last_pos.y};
	a_star_path(game, npc, start, goal);
}

/**
 * @brief Checks if the NPC has a valid follow path.
 *
 * A path is considered valid if it is not NULL and contains at least one point.
 *
 * @param npc Pointer to the NPC whose path is being checked.
 * @return true if the path exists and has a positive length, false otherwise.
 */
static bool	is_follow_path_valid(t_npc *npc)
{
	return (npc->path && npc->path_length > 0);
}

/**
 * @brief Moves the NPC along the follow path toward the player.
 *
 * If the NPC has no valid path, a new one is calculated using the player's
 * last position as the goal. If the NPC reaches the current path target, it
 * progresses to the next point in the path. If the end of the path is reached,
 * a new path is recalculated from the NPC's current position.
 *
 * @param game Pointer to the game structure.
 * @param npc Pointer to the NPC to be moved.
 * @param delta_time Time elapsed since the last frame.
 */
void	move_npc_follow(t_game *game, t_npc *npc, double delta_time)
{
	t_dpoint	target;

	if (!is_follow_path_valid(npc))
	{
		update_npc_follow_path(game, &game->player, npc);
		if (!is_follow_path_valid(npc))
			return ;
	}
	target = npc->path[npc->path_index];
	if (move_npc(game, npc, target, delta_time))
	{
		npc->path_index++;
		if (npc->path_index >= npc->path_length)
		{
			update_npc_follow_path(game, &game->player, npc);
			npc->path_index = 0;
		}
	}
}
