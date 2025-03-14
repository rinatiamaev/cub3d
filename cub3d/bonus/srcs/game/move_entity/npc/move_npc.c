/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:23:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 23:59:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_position_occupied_by_other_npc(t_game *game, t_npc *npc,
	t_dpoint next_pos)
{
	int i;

	i = 0;
	while (i < game->npc_count)
	{
		
		if (npc && game->npcs[i] == npc)
		{
			i++;
			continue ;
		}
		if ((int)game->npcs[i]->pos.x == (int)next_pos.x
			&& (int)game->npcs[i]->pos.y == (int)next_pos.y)
			return (true);
		i++;
	}
	return (false);
}

static bool	has_reached_target(t_npc *npc, t_dpoint target)
{
	return (ft_cab_dist_dpoint(npc->pos, target) < npc->threshold_dist);
}

static void	stop_npc(t_npc *npc, t_dpoint target)
{
	npc->pos.x = target.x;
	npc->pos.y = target.y;
	npc->move_vec = (t_dpoint){0, 0};
}

bool	move_npc(t_game *game, t_npc *npc, t_dpoint target, double delta_time)
{
	t_dpoint	delta;
	t_dpoint	next_pos;
	double		dist;

	if (npc->is_hit || is_any_npc_talking(game))
	{
		stop_npc(npc, npc->pos);
		return (true);
	}
	delta.x = target.x - npc->pos.x;
	delta.y = target.y - npc->pos.y;
	if (has_reached_target(npc, target))
	{
		stop_npc(npc, target);
		return (true);
	}
	dist = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	if (dist == 0)
	{
		stop_npc(npc, npc->pos);
		return (true);
	}
	delta.x /= dist;
	delta.y /= dist;
	next_pos.x = npc->pos.x + (delta.x * npc->speed * delta_time);
	next_pos.y = npc->pos.y + (delta.y * npc->speed * delta_time);
	if (is_position_occupied_by_other_npc(game, npc, next_pos))
	{
		if (npc->is_following)
		{
			bool is_blocked = true;
			if (is_blocked)
			{
				npc->is_following = false;
				npc->state = WAIT;
			}
		}
		else if (npc->state == PATROL)
			generate_npc_waypoints(npc, game);
		return (true);
	}
	npc->pos = next_pos;
	npc->move_vec.x = delta.x;
	npc->move_vec.y = delta.y;
	return (false);
}

