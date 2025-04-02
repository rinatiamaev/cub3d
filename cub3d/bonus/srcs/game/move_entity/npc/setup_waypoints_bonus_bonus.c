/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_waypoints_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:04:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:32:27 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
