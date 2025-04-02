/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_all_npcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:46:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:29:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	npc_interact_with_door(t_game *game, t_npc *npc)
{
	t_door	*door;
	double	range;
	int		i;
	double	current_distance;

	door = NULL;
	range = 1.5;
	i = 0;
	while (i < game->door_count)
	{
		current_distance = ft_cab_dist_dpoint(npc->pos, game->doors[i]->pos);
		if (current_distance <= range)
		{
			door = game->doors[i];
			break ;
		}
		i++;
	}
	if (!door)
		return (false);
	if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENING;
	return (true);
}

void	update_all_npcs(t_game *game, double delta_time)
{
	t_npc	*npc;
	int		i;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (!npc->is_enemy)
		{
			update_npc(game, npc, delta_time);
			if (npc->state == FOLLOW)
				npc_interact_with_door(game, npc);
		}
		else
			update_enemy_npc(game, npc, delta_time);
		i++;
	}
}
