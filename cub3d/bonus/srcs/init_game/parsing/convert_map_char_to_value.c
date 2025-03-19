/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_char_to_value.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:39:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 10:25:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	spawn_entity_at_position(t_game *game, char cell,
															double x, double y)
{
	if (cell == 'K')
		spawn_witch_kitty(game, x, y);
	else if (cell == 'C')
		spawn_calico_kitty(game, x, y);
	else if (cell == 'D')
		spawn_door(game, x, y);
	else if (cell == 'F')
		spawn_fire_spirit(game, x, y);
	else if (cell == 'P')
		spawn_well(game, x, y);
	else if (cell == 'B')
		spawn_bucket(game, x, y);
	else if (cell == 'T')
		spawn_tree(game, x, y);
	else if (cell == 'I')
		spawn_key(game, x, y);
	else if (cell == 'X')
		spawn_exit_door(game, x, y);
}

static int	get_entity_map_value(char cell)
{
	if (cell == 'K' || cell == 'C' || cell == 'F'
		|| cell == 'T' || cell == 'I')
		return (FREE_SPACE);
	if (cell == 'D')
		return (DOOR);
	if (cell == 'X')
		return (EXIT_DOOR);
	if (cell == 'P')
		return (WELL);
	if (cell == 'B')
		return (BUCKET);
	return (EMPTY);
}

static int	spawn_entity(t_game *game, char cell, int x, int y)
{
	spawn_entity_at_position(game, cell, (double)x, (double)y);
	return (get_entity_map_value(cell));
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
