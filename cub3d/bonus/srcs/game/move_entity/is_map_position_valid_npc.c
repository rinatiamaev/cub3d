/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_position_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:12:02 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/21 12:12:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_wall(t_game *game, t_point pos)
{
	return (game->map->matrix[(int)(pos.y)][(int)pos.x] == WALL);
}

bool	is_map_position_valid_npc(t_game *game, t_dpoint pos)
{
	t_point			grid_pos;

	grid_pos = (t_point){(int)pos.x, (int)pos.y};
	if (is_wall(game, grid_pos))
		return (false);
	if (!is_within_bounds(game, grid_pos))
		return (false);
	return (true);
}
