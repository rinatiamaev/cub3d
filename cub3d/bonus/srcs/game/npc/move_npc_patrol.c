/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc_patrol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:29:13 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 19:49:02 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_npc_patrol_path(t_game *game, t_npc *npc)
{
	a_star_path(game, npc, (t_point){(int)npc->pos.x, (int)npc->pos.y},
		(t_point){(int)npc->waypoints[npc->current_wp].x,
		(int)npc->waypoints[npc->current_wp].y});
}

static void	update_npc_follow_path(t_game *game, t_npc *npc)
{
	a_star_path(game, npc, (t_point){(int)npc->pos.x, (int)npc->pos.y},
		(t_point){(int)game->player.last_pos.x, (int)game->player.last_pos.y});
}

static void update_npc_path(t_game *game, t_npc *npc)
{
	if (npc->state == NPC_STATE_FOLLOW)
		update_npc_follow_path(game, npc);
	else
		update_npc_patrol_path(game, npc);
}

static bool is_path_valid(t_npc *npc)
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
		update_npc_path(game, npc);
	}
}

void move_npc_plan(t_game *game, t_npc *npc, double delta_time)
{
	if (npc->state == NPC_STATE_FOLLOW)
	{
		if ((int)npc->pos.x != (int)game->player.last_pos.x
			|| (int)npc->pos.y != (int)game->player.last_pos.y)
		{
			update_npc_path(game, npc);
		}
	}
	else if (npc->state == NPC_STATE_PATROL)
	{
		if (!is_path_valid(npc))
		{
			update_npc_path(game, npc);
			if (!is_path_valid(npc))
			{
				generate_npc_waypoints(npc, game);
				return ;
			}
		}
	}
	t_dpoint target = npc->path[npc->path_index];
	if (move_npc(npc, target, delta_time))
	{
		if (npc->state == NPC_STATE_PATROL)
			handle_waypoint_progression(game, npc);
	}
}
