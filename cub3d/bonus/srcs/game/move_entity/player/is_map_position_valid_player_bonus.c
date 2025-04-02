/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_position_valid_player.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:13:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:33:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_blocked(t_game *game, t_dpoint pos)
{
	t_point	grid_pos;

	grid_pos = (t_point){(int)pos.x, (int)pos.y};
	return (!is_within_bounds(game, grid_pos) || is_wall(game, grid_pos));
}

bool	is_map_position_valid_player(t_game *game, t_dpoint pos)
{
	t_dpoint	checks[4];
	int			i;

	if (is_blocked(game, pos))
		return (false);
	checks[0] = (t_dpoint){pos.x - 0.1, pos.y};
	checks[1] = (t_dpoint){pos.x + 0.1, pos.y};
	checks[2] = (t_dpoint){pos.x, pos.y - 0.1};
	checks[3] = (t_dpoint){pos.x, pos.y + 0.1};
	i = 0;
	while (i < 4)
	{
		if (is_blocked(game, checks[i]))
			return (false);
		i++;
	}
	return (true);
}
