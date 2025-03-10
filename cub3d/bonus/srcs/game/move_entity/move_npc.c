/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:23:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 14:28:18 by nlouis           ###   ########.fr       */
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

static void	update_npc_movement(t_npc *npc, t_dpoint delta, double delta_time)
{
	double	dist;

	dist = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= dist;
	delta.y /= dist;
	npc->pos.x += delta.x * npc->speed * delta_time;
	npc->pos.y += delta.y * npc->speed * delta_time;
	npc->move_vec.x = delta.x;
	npc->move_vec.y = delta.y;
}

static bool	is_target_occupied_by_npc(t_game *game, t_npc *npc, t_dpoint target)
{
	int	i;

	i = 0;
	while (i < game->npc_count)
	{
		if (game->npcs[i] != npc
			&& has_reached_target(game->npcs[i], target))
			return (true);
		i++;
	}
	return (false);
}

bool	move_npc(t_game *game, t_npc *npc, t_dpoint target, double delta_time)
{
	t_dpoint	delta;

	delta.x = target.x - npc->pos.x;
	delta.y = target.y - npc->pos.y;
	if (has_reached_target(npc, target))
	{
		stop_npc(npc, target);
		return (true);
	}
	if (is_target_occupied_by_npc(game, npc, target))
		return (false);
	update_npc_movement(npc, delta, delta_time);
	return (false);
}
