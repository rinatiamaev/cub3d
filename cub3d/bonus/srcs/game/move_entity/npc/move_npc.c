/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:23:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 09:41:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	double		dist;
	t_dpoint	delta;
	
	if (npc->is_hit || is_any_npc_talking(game))
		return (true);
	if (has_reached_target(npc, target))
	{
		stop_npc(npc, npc->pos);
		return (true);
	}
	delta.x = target.x - npc->pos.x;
	delta.y = target.y - npc->pos.y;
	dist = ft_cab_dist_dpoint(npc->pos, target);
	if (dist == 0.0)
		return (true);
	delta.x /= dist;
	delta.y /= dist;
	npc->pos.x += delta.x * npc->speed * delta_time;
	npc->pos.y += delta.y * npc->speed * delta_time;
	npc->move_vec = delta;
	return (false);
}





