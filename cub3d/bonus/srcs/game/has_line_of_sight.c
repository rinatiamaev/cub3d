/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_line_of_sight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:50:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 16:24:33 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_los_data(t_los *los, t_dpoint src, t_dpoint target)
{
	los->ray_dir.x = target.x - src.x;
	los->ray_dir.y = target.y - src.y;
	los->map_check.x = (int)src.x;
	los->map_check.y = (int)src.y;
	if (los->ray_dir.x != 0)
		los->delta_dist.x = fabs(1.0 / los->ray_dir.x);
	else
		los->delta_dist.x = 1000000.0;
	if (los->ray_dir.y != 0)
		los->delta_dist.y = fabs(1.0 / los->ray_dir.y);
	else
		los->delta_dist.y = 1000000.0;
}

static void	calculate_step_and_side_dist(t_los *los, t_dpoint src)
{
	if (los->ray_dir.x < 0)
	{
		los->step.x = -1;
		los->side_dist.x
			= (src.x - los->map_check.x) * los->delta_dist.x;
	}
	else
	{
		los->step.x = 1;
		los->side_dist.x
			= (los->map_check.x + 1.0 - src.x) * los->delta_dist.x;
	}
	if (los->ray_dir.y < 0)
	{
		los->step.y = -1;
		los->side_dist.y
			= (src.y - los->map_check.y) * los->delta_dist.y;
	}
	else
	{
		los->step.y = 1;
		los->side_dist.y
			= (los->map_check.y + 1.0 - src.y) * los->delta_dist.y;
	}
}

static bool	perform_los_dda(t_game *game, t_los *los, t_dpoint target)
{
	while (true)
	{
		if (los->side_dist.x < los->side_dist.y)
		{
			los->side_dist.x += los->delta_dist.x;
			los->map_check.x += los->step.x;
		}
		else
		{
			los->side_dist.y += los->delta_dist.y;
			los->map_check.y += los->step.y;
		}
		if (los->map_check.x < 0 || los->map_check.x >= game->map->size.x
			|| los->map_check.y < 0 || los->map_check.y >= game->map->size.y)
			return (false);
		if (game->map->matrix[los->map_check.y][los->map_check.x] == WALL
			|| game->map->matrix[los->map_check.y][los->map_check.x] == DOOR)
			return (false);
		if (los->map_check.x == (int)target.x
			&& los->map_check.y == (int)target.y)
			return (true);
	}
}

bool	has_line_of_sight(t_game *game, t_dpoint src, t_dpoint target)
{
	t_los	los;

	init_los_data(&los, src, target);
	calculate_step_and_side_dist(&los, src);
	return (perform_los_dda(game, &los, target));
}
