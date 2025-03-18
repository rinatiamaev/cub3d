/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_char_to_value.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:39:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 10:26:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	spawn_entity(t_game *game, char cell, int x, int y)
{
	if (cell == 'K')
	{
		spawn_witch_kitty(game, (double)x, (double)y);
		return (FREE_SPACE);
	}
	else if (cell == 'C')
	{
		spawn_calico_kitty(game, (double)x, (double)y);
		return (FREE_SPACE);
	}
	else if (cell == 'D')
	{
		spawn_door(game, (double)x, (double)y);
		return (DOOR);
	}
	else if (cell == 'F')
	{
		spawn_fire_spirit(game, (double)x, (double)y);
		return (FREE_SPACE);
	}
	return (EMPTY);
}

int	convert_map_char_to_value(t_game *game, t_map *map, int i, int j)
{
	char	cell;

	cell = map->map_layout[i][j];
	if (cell == '1')
		return (WALL);
	else if (ft_strchr("NSEW", cell))
		return (CONF_DIR);
	else if (cell == '0')
		return (FREE_SPACE);
	else
		return (spawn_entity(game, cell, j, i));
}
