/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_position_valid_for_player.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:44:16 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 12:16:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool is_door_walkable_player(t_game *game, t_point pos)
{
	t_door	*door;

	door = find_door_at(game, pos);
	if (!door)
		return (true);
	return (door->state == DOOR_OPEN);
}

static bool	is_position_near_any_npc(t_dpoint position, t_game *game,
	double min_distance, t_npc *self_npc)
{
	t_npc	*npc;
	double	distance;
	int		i;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (self_npc && npc == self_npc)
		{
			i++;
			continue ;
		}
		distance = ft_cab_dist_dpoint(position, npc->pos);
		if (distance < min_distance)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_position_near_any_item(t_dpoint position, t_game *game,
														double min_distance)
{
	t_item	*item;
	double	distance;
	int		i;

	if (!game->items || game->item_count == 0)
		return (false);
	i = 0;
	while (i < game->item_count)
	{
		item = game->items[i];
		distance = ft_cab_dist_dpoint(position, item->pos);
		if (distance < min_distance)
			return (true);
		i++;
	}
	return (false);
}

bool	is_position_valid_for_player(t_game *game, t_dpoint pos)
{
	if (!is_map_position_valid(game, pos))
		return (false);
	if (is_position_near_any_npc(pos, game, 0.3, NULL))
		return (false);
	if (is_position_near_any_item(pos, game, 0.6))
		return (false);
	if (!is_door_walkable_player(game, (t_point){(int)pos.x, (int)pos.y}))
		return (false);
	return (true);
}
