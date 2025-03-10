/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_char_to_value.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:39:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 14:56:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	convert_map_char_to_value(t_game *game, t_map *map, int i, int j)
{
	char	cell;

	cell = map->map_layout[i][j];
	if (cell == '1')
		return (WALL);
	else if (ft_strchr("NSEW", cell))
		return (CONF_DIR);
	else if (cell == 'K')
	{
		spawn_witch_kitty(game, (double)j, (double)i);
		return (WITCH_KITTY);
	}
	else if (cell == 'C')
	{
		spawn_calico_kitty(game, (double)j, (double)i);
		return (CALICO_KITTY);
	}
	else if (cell == 'D')
	{
		spawn_door(game, (double)j, (double)i);
		return (DOOR);
	}
	else if (cell == '0')
		return (FREE_SPACE);
	else
		return (EMPTY);
}
