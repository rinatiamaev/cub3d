/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_position_valid_npc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:07:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/12 00:57:21 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool is_occupied_by_moving_npc(t_game *game, t_point pos)
{
    int i;

    i = 0;
    while (i < game->npc_count)
    {
        if ((int)game->npcs[i]->pos.x == pos.x && (int)game->npcs[i]->pos.y == pos.y
            && (game->npcs[i]->move_vec.x != 0 || game->npcs[i]->move_vec.y != 0))
            return (true);
        i++;
    }
    return (false);
}

bool	is_occupied_by_any_npc(t_game *game, t_point pos)
{
	int i;

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

bool is_position_valid_for_npc(t_game *game, t_astar *astar, t_point pos)
{
    if (!is_map_position_valid(game, (t_dpoint){(double)pos.x, (double)pos.y}))
        return (false);
    if (astar->open_list[pos.y][pos.x])
        return (false);
    if (is_occupied_by_moving_npc(game, pos))
        return (true);
    if (is_occupied_by_any_npc(game, pos))
        return (false);
    return (true);
}
