/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:23:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:30:44 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	has_reached_target(t_npc *npc, t_dpoint target)
{
	double	distance_to_target;

	distance_to_target = ft_cab_dist_dpoint(npc->pos, target);
	return (distance_to_target < npc->threshold_dist);
}

static void	stop_npc(t_npc *npc, t_dpoint target)
{
	npc->pos.x = target.x;
	npc->pos.y = target.y;
	npc->move_vec = (t_dpoint){0, 0};
}

static bool	should_stop_npc(t_game *game, t_npc *npc, t_dpoint target)
{
	if (npc->is_hit)
		return (true);
	if (is_any_npc_talking(game))
		return (true);
	if (has_reached_target(npc, target))
		return (true);
	return (false);
}

static double	get_current_speed(t_npc *npc)
{
	if (npc->is_following)
		return (npc->following_speed);
	return (npc->speed);
}

bool	move_npc(t_game *game, t_npc *npc, t_dpoint target, double delta_time)
{
	double		current_speed;
	double		step;

	if (should_stop_npc(game, npc, target))
	{
		if (has_reached_target(npc, target))
			stop_npc(npc, npc->pos);
		return (true);
	}
	current_speed = get_current_speed(npc);
	npc->move_vec = get_unit_direction_vector(npc->pos, target);
	step = current_speed * delta_time;
	npc->pos.x += npc->move_vec.x * step;
	npc->pos.y += npc->move_vec.y * step;
	return (false);
}
