/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc_patrol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:29:13 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/21 12:54:42 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static bool	is_patrol_path_valid(t_npc *npc)
{
	return (npc->path && npc->path_length > 0);
}

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
