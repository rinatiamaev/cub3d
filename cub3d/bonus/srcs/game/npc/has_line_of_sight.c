/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_line_of_sight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:50:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 20:26:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_los_data(t_los *los, t_npc *npc, t_player *player)
{
	los->ray_dir.x = player->pos.x - npc->pos.x;
	los->ray_dir.y = player->pos.y - npc->pos.y;
	los->map_check.x = (int)npc->pos.x;
	los->map_check.y = (int)npc->pos.y;
	los->delta_dist.x = fabs(1.0 / los->ray_dir.x);
	los->delta_dist.y = fabs(1.0 / los->ray_dir.y);
}

static void	calculate_step_and_side_dist(t_los *los, t_npc *npc)
{
	if (los->ray_dir.x < 0)
	{
		los->step.x = -1;
		los->side_dist.x
			= (npc->pos.x - los->map_check.x) * los->delta_dist.x;
	}
	else
	{
		los->step.x = 1;
		los->side_dist.x
			= (los->map_check.x + 1.0 - npc->pos.x) * los->delta_dist.x;
	}

	if (los->ray_dir.y < 0)
	{
		los->step.y = -1;
		los->side_dist.y
			= (npc->pos.y - los->map_check.y) * los->delta_dist.y;
	}
	else
	{
		los->step.y = 1;
		los->side_dist.y
			= (los->map_check.y + 1.0 - npc->pos.y) * los->delta_dist.y;
	}
}

static bool	perform_los_dda(t_game *game, t_los *los, t_player *player)
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
		if (game->map->matrix[los->map_check.y][los->map_check.x] == WALL)
			return (false);
		if (los->map_check.x == (int)player->pos.x
			&& los->map_check.y == (int)player->pos.y)
			return (true);
	}
}

bool	has_line_of_sight(t_game *game, t_npc *npc, t_player *player)
{
	t_los	los;

	init_los_data(&los, npc, player);
	calculate_step_and_side_dist(&los, npc);
	return (perform_los_dda(game, &los, player));
}

