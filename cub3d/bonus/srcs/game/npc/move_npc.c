/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:23:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 02:39:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	move_npc(t_npc *npc, t_dpoint target, double delta_time)
{
	t_dpoint	delta;
	double		dist_sq;
	double		dist;

	delta.x = target.x - npc->pos.x;
	delta.y = target.y - npc->pos.y;
	dist_sq = (delta.x * delta.x) + (delta.y * delta.y);
	if (dist_sq < (npc->threshold_dist * npc->threshold_dist))
	{
		npc->pos.x = target.x;
		npc->pos.y = target.y;
		npc->move_vec = (t_dpoint){0, 0};
		return (true);
	}
	dist = sqrt(dist_sq);
	delta.x /= dist;
	delta.y /= dist;
	npc->pos.x += delta.x * npc->speed * delta_time;
	npc->pos.y += delta.y * npc->speed * delta_time;
	npc->move_vec.x = delta.x;
	npc->move_vec.y = delta.y;
	return (false);
}

void	move_npc_patrol(t_game *game, t_npc *npc, double delta_time)
{
	t_dpoint	target;

	if (!npc->path)
	{
		a_star_path(game, npc,(t_point){(int)npc->pos.x, (int)npc->pos.y},
					(t_point){(int)npc->waypoints[npc->current_wp].x,
							(int)npc->waypoints[npc->current_wp].y});
		if (!npc->path || npc->path_length == 0)
			return ;
	}
	target = npc->path[npc->path_index];
	if (move_npc(npc, target, delta_time))
	{
		npc->path_index++;
		if (npc->path_index == npc->waypoint_count)
			generate_npc_waypoints(npc, game);
		if (npc->path_index >= npc->path_length)
		{
			npc->path_index = 0;
			npc->path_length = 0;
			npc->current_wp = (npc->current_wp + 1) % npc->waypoint_count;
			a_star_path(game, npc,
						(t_point){(int)npc->pos.x, (int)npc->pos.y},
						(t_point){(int)npc->waypoints[npc->current_wp].x,
								(int)npc->waypoints[npc->current_wp].y});
		}
	}
}


