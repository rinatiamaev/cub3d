/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_position_valid_npc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:07:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:31:42 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_door_walkable_npc(t_game *game, t_npc *npc, t_point pos)
{
	t_door	*door;

	door = find_door_at(game, pos);
	if (!door)
		return (true);
	if (npc->state == FOLLOW)
		return (true);
	return (false);
}

static bool	is_occupied_by_any_npc(t_game *game, t_point pos)
{
	int	i;

	i = 0;
	while (i < game->npc_count)
	{
		if ((int)game->npcs[i]->pos.x == pos.x
			&& (int)game->npcs[i]->pos.y == pos.y)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_map_position_valid_npc(t_game *game, t_dpoint pos)
{
	t_point			grid_pos;

	grid_pos = (t_point){(int)pos.x, (int)pos.y};
	if (is_wall(game, grid_pos))
		return (false);
	if (!is_within_bounds(game, grid_pos))
		return (false);
	return (true);
}

bool	is_position_valid_npc(t_game *game, t_npc *npc, t_astar *astar,
																t_point pos)
{
	if (!is_map_position_valid_npc(game,
			(t_dpoint){(double)pos.x, (double)pos.y}))
		return (false);
	if (astar && astar->open_list[pos.y][pos.x])
		return (false);
	if (is_occupied_by_any_npc(game, pos))
		return (false);
	if (!is_door_walkable_npc(game, npc, pos))
		return (false);
	return (true);
}
