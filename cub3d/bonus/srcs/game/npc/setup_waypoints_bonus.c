/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_waypoints_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:04:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 14:23:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_patrol_point_valid(t_game *game, t_dpoint pos)
{
	t_point	check_pos;

	check_pos = (t_point){pos.x, pos.y};
	if (pos.y < 0 || pos.y >= game->map->size.y
		|| pos.x < 0 || pos.x >= game->map->size.x)
		return (false);
	if (game->map->matrix[check_pos.y][check_pos.x] != FREE_SPACE)
		return (false);
	return (true);
}

static int	is_patrol_point_unique(t_npc *npc, int count, t_dpoint pos)
{
	int		i;
	double	min_dist;

	i = 0;
	min_dist = 2.0;
	while (i < count)
	{
		if (npc->waypoints[i].x == pos.x && npc->waypoints[i].y == pos.y)
			return (false);
		if (ft_manhattan_dist_dpoint(npc->waypoints[i], pos) < min_dist)
			return (false);
		i++;
	}
	return (true);
}

static t_dpoint	generate_point(t_dpoint pos, int range)
{
	int	offset_x;
	int	offset_y;

	offset_x = (ft_time_seeded_rand() % (2 * range + 1)) - range;
	offset_y = (ft_time_seeded_rand() % (2 * range + 1)) - range;
	return ((t_dpoint){pos.x + offset_x, pos.y + offset_y});
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
	npc->waypoints = x_calloc(game, 1, npc->waypoint_count * sizeof(t_dpoint));
}

void	generate_npc_waypoints(t_npc *npc, t_game *game)
{
	int			count;
	int			attempts;
	int			max_attempts;
	t_dpoint	pos;

	allocate_npc_waypoints(npc, game);
	count = 0;
	attempts = 0;
	max_attempts = 15000;
	while (count < npc->waypoint_count && attempts < max_attempts)
	{
		pos = generate_point(npc->pos, npc->patrol_range);
		if (is_patrol_point_valid(game, pos)
			&& is_patrol_point_unique(npc, count, pos))
		{
			npc->waypoints[count] = pos;
			count++;
			attempts = 0;
		}
		else
			attempts++;
	}
}
