/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_move_valid.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:44:16 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/22 17:19:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_position_near_npc(t_game *game, t_dpoint next_pos)
{
	t_npc	*npc;
	double	npc_distance;
	double	minimum_distance;
	int		i;

	i = 0;
	minimum_distance = 0.3;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		npc_distance = ft_cab_dist_dpoint(next_pos, npc->pos);
		if (npc_distance < minimum_distance)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_position_near_item(t_game *game, t_dpoint next_pos)
{
	t_item	*item;
	double	item_distance;
	double	minimum_distance;
	int		i;

	i = 0;
	minimum_distance = 0.6;
	while (i < game->item_count)
	{
		item = game->items[i];
		item_distance = ft_cab_dist_dpoint(next_pos, item->pos);
		if (item_distance < minimum_distance)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_door_walkable_player(t_game *game, t_point grid_pos)
{
	t_door	*door;

	door = find_door_at(game, grid_pos);
	if (!door)
		return (true);
	return (door->state == DOOR_OPEN);
}

bool	is_player_move_valid(t_game *game, t_dpoint next_pos)
{
	t_point	grid_pos;

	grid_pos = (t_point){(int)next_pos.x, (int)next_pos.y};
	if (!is_map_position_valid_player(game, next_pos))
		return (false);
	if (is_position_near_npc(game, next_pos))
		return (false);
	if (is_position_near_item(game, next_pos))
		return (false);
	if (!is_door_walkable_player(game, grid_pos))
		return (false);
	return (true);
}
