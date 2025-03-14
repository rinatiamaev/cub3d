/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_position_valid_for_player.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:44:16 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 23:36:30 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_position_near_any_npc(t_dpoint position, t_game *game,
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

bool	is_position_valid_for_player(t_game *game, t_dpoint pos)
{
	if (!is_map_position_valid(game, pos))
		return (false);
	if (is_position_near_any_npc(pos, game, 0.3, NULL))
		return (false);
	return (true);
}
